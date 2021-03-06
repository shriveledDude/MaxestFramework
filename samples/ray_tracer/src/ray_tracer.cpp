#include "ray_tracer.h"


bool NRayTracer::SceneIntersection_Primary(const SScene& scene, const SVector3& rayStart, const SVector3& rayDir, float maxDistance, SSceneIntersectionResult& sceneIntersectionResult)
{
	float closestDistance = cFloatMax;
	SVector3 tempIntersectionPoint;
	float tempDistance;

	for (uint i = 0; i < scene.triangles.size(); i++)
	{
		if (IntersectionRayTriangle(rayStart, rayDir, scene.triangles[i].p1, scene.triangles[i].p2, scene.triangles[i].p3, tempIntersectionPoint, tempDistance))
		{
			if (tempDistance < 0.0f)
				continue;
			if (tempDistance > closestDistance)
				continue;
			if (tempDistance > maxDistance)
				continue;
			// backface culling
			if (Dot(rayDir, scene.triangles[i].normal) > 0.0f)
				continue;

			sceneIntersectionResult.materialIndex = scene.triangles[i].materialIndex;
			sceneIntersectionResult.point = tempIntersectionPoint;
			sceneIntersectionResult.normal = scene.triangles[i].normal;
			sceneIntersectionResult.backside = false;
			sceneIntersectionResult.triangleIndex = i;

			closestDistance = tempDistance;
		}
	}

	for (uint i = 0; i < scene.spheres.size(); i++)
	{
		if (IntersectionRaySphere(rayStart, rayDir, scene.spheres[i].position, scene.spheres[i].radius, tempIntersectionPoint, tempDistance))
		{
			if (tempDistance < 0.0f)
				continue;
			if (tempDistance > closestDistance)
				continue;
			if (tempDistance > maxDistance)
				continue;

			sceneIntersectionResult.materialIndex = scene.spheres[i].materialIndex;
			sceneIntersectionResult.point = tempIntersectionPoint;
			sceneIntersectionResult.normal = 1.0f / scene.spheres[i].radius * (tempIntersectionPoint - scene.spheres[i].position);
			sceneIntersectionResult.backside = false;
			sceneIntersectionResult.triangleIndex = -1;

			// are we inside the sphere?
			if (Distance(rayStart, scene.spheres[i].position) < scene.spheres[i].radius)
			{
				sceneIntersectionResult.normal = -sceneIntersectionResult.normal;
				sceneIntersectionResult.backside = true;
			}

			closestDistance = tempDistance;
		}
	}

	return closestDistance != cFloatMax;
}


bool NRayTracer::SceneIntersection_Shadow(const SScene& scene, const SVector3& rayStart, const SVector3& rayDir, float maxDistance, int triangleIndex)
{
	float closestDistance = cFloatMax;
	SVector3 tempIntersectionPoint;
	float tempDistance;

	for (uint i = 0; i < scene.triangles.size(); i++)
	{
		if ((int)i == triangleIndex)
			continue;

		if (IntersectionRayTriangle(rayStart, rayDir, scene.triangles[i].p1, scene.triangles[i].p2, scene.triangles[i].p3, tempIntersectionPoint, tempDistance))
		{
			if (tempDistance < 0.0f)
				continue;
			if (tempDistance > closestDistance)
				continue;
			if (tempDistance > maxDistance)
				continue;

			closestDistance = tempDistance;
		}
	}

	for (uint i = 0; i < scene.spheres.size(); i++)
	{
		// sphere use offset instead of "triangleIndex" because sphere can occlude itself
		if (IntersectionRaySphere(rayStart + 0.001f*rayDir, rayDir, scene.spheres[i].position, scene.spheres[i].radius, tempIntersectionPoint, tempDistance))
		{
			if (tempDistance < 0.0f)
				continue;
			if (tempDistance > closestDistance)
				continue;
			if (tempDistance > maxDistance)
				continue;

			closestDistance = tempDistance;
		}
	}

	return closestDistance != cFloatMax;
}


SVector3 NRayTracer::SceneRadiance_Recursive(const SScene& scene, int samplesSetIndex, const SVector3& rayStart, const SVector3& rayDir, int depth, int maxDepth)
{
	SVector3 radiance = cVector3Zero;
	SSceneIntersectionResult sir;

	if (depth == maxDepth)
		return radiance;

	if (SceneIntersection_Primary(scene, rayStart, rayDir, cFloatMax, sir))
	{
		const SMaterial& material = scene.materials[sir.materialIndex];
		SMatrix worldToTangent = WorldToTangent(sir.normal);
		SVector3& point = sir.point;
		SVector3 wo = -Normalize(rayDir);
		SVector3 wo_tangent = wo * worldToTangent;
		SVector3& normal = sir.normal;
		SVector3 normal_tangent = sir.normal * worldToTangent;
		bool& backside = sir.backside;
		int32& triangleIndex = sir.triangleIndex;

		MF_ASSERT(material.diffuseBRDF != nullptr);
		MF_ASSERT(material.specularBRDF != nullptr);

		// ambient
	/*	{
			SVector3 ambient = cVector3Zero;

			for (uint i = 0; i < scene.samples_hemisphere1[samplesSetIndex].size(); i++)
			{
				SVector3 wi = SphericalToCartesian(scene.samples_hemisphere1[samplesSetIndex][i]);
				wi = wi * tangentToWorld;

				if (!SceneIntersection_Shadow(scene, point, wi, cFloatMax, triangleIndex))
					ambient = ambient + cVector3One;
			}

			ambient /= (float)scene.samples_hemisphere1[samplesSetIndex].size();
			ambient *= material.diffuseBRDF->rho();
			radiance += ambient; // BRDF is assumed to be Lambertian
		}*/
		radiance += scene.ambientLightingScale * cVector3One;

		// direct illumination

		// dir lights
		for (uint i = 0; i < scene.dirLights.size(); i++)
		{
			const SDirLight& light = scene.dirLights[i];

			SVector3 wi = -light.dir;
			SVector3 wi_tangent = Normalize(wi * worldToTangent);

			if (!SceneIntersection_Shadow(scene, point, wi, cFloatMax, triangleIndex))
			{
				float NdotL = Saturate(Dot(wi, normal));

				radiance +=
					(material.diffuseBRDF->f(wi_tangent, wo_tangent, normal_tangent) +
					material.specularBRDF->f(wi_tangent, wo_tangent, normal_tangent)) *
					light.color *
					NdotL;
			}
		}

		// point lights
		for (uint i = 0; i < scene.pointLights.size(); i++)
		{
			const SPointLight& light = scene.pointLights[i];

			SVector3 wi = light.position - point;
			float distanceToLight = Length(wi);
			wi = wi / distanceToLight;
			SVector3 wi_tangent = Normalize(wi * worldToTangent);

			if (!SceneIntersection_Shadow(scene, point, wi, 1.1f*distanceToLight, triangleIndex))
			{
				float NdotL = Saturate(Dot(wi, normal));

				radiance +=
					(material.diffuseBRDF->f(wi_tangent, wo_tangent, normal_tangent) +
					material.specularBRDF->f(wi_tangent, wo_tangent, normal_tangent)) *
					light.color * (1.0f / Sqr(distanceToLight)) *
					NdotL;
			}
		}

		// indirect illumination

		float transmittance = material.transmittance;
		float reflectivity = material.reflectivity;

		if (transmittance > 0.0f)
		{
			float eta = material.transmittanceEta;
			float NdotV = Dot(wo, normal);

			if (backside)
				eta = 1.0f / eta;

			float NdotT = 1.0f - (1.0f - Sqr(NdotV)) / Sqr(eta);

			if (NdotT >= 0.0f)
			{
				NdotT = Sqrt(NdotT);
				SVector3 wi = -wo/eta - (NdotT - NdotV/eta) * normal;

				radiance +=
					transmittance /
					Sqr(eta) *
					SceneRadiance_Recursive(scene, samplesSetIndex, point + 0.001f*wi, wi, depth + 1, maxDepth);
			}
			else // total internal reflection
			{
				reflectivity += transmittance;
			}
		}

		if (reflectivity > 0.0f)
		{
			SVector3 wi = Reflect(-wo, normal);

			radiance +=
				reflectivity *
				SceneRadiance_Recursive(scene, samplesSetIndex, point + 0.001f*wi, wi, depth + 1, maxDepth);
		}

		// GI
	/*	for (int i = 0; i < 10; i++)
		{
			float u = RandomFloat();
			float v = RandomFloat();

			Spherical spherical;
			spherical.theta = ACos(2.0f*v - 1.0f);
			spherical.phi = 2.0f * Pi * u;

			SVector3 cartesian = SphericalToCartesian(spherical);
			NormalizeIn(cartesian);

			float dot = Dot(sir.normal, cartesian);

			if (dot < 0.0f)
			{
				cartesian = -cartesian;
				dot = -dot;
			}

			radiance += brdf * dot * SceneRadiance(scene, eye, sir.intersectionPoint + 0.01f*cartesian, cartesian, level + 1) / 10.0f;
		}*/
	}

	return radiance;
}


void NRayTracer::SceneAddMesh(SScene& scene, const NMesh::SMesh& mesh, const SMatrix& transform, int materialIndex)
{
	for (uint i = 0; i < mesh.chunks.size(); i++)
		MF_ASSERT(mesh.chunks[i].indices.size() != 0);

	STrianglePrimitive triangle;
	triangle.materialIndex = materialIndex;

	for (uint i = 0; i < mesh.chunks.size(); i++)
	{
		for (uint j = 0; j < mesh.chunks[i].indices.size() / 3; j++)
		{
			triangle.p1 = VectorCustom(
				mesh.chunks[i].vertices[mesh.chunks[i].indices[3 * j + 0]].position.x,
				mesh.chunks[i].vertices[mesh.chunks[i].indices[3 * j + 0]].position.y,
				mesh.chunks[i].vertices[mesh.chunks[i].indices[3 * j + 0]].position.z);
			triangle.p2 = VectorCustom(
				mesh.chunks[i].vertices[mesh.chunks[i].indices[3 * j + 1]].position.x,
				mesh.chunks[i].vertices[mesh.chunks[i].indices[3 * j + 1]].position.y,
				mesh.chunks[i].vertices[mesh.chunks[i].indices[3 * j + 1]].position.z);
			triangle.p3 = VectorCustom(
				mesh.chunks[i].vertices[mesh.chunks[i].indices[3 * j + 2]].position.x,
				mesh.chunks[i].vertices[mesh.chunks[i].indices[3 * j + 2]].position.y,
				mesh.chunks[i].vertices[mesh.chunks[i].indices[3 * j + 2]].position.z);

			triangle.p1 = TransformPoint(triangle.p1, transform);
			triangle.p2 = TransformPoint(triangle.p2, transform);
			triangle.p3 = TransformPoint(triangle.p3, transform);

			triangle.normal = TriangleNormal(triangle.p1, triangle.p2, triangle.p3);

			scene.triangles.push_back(triangle);
		}
	}
}
