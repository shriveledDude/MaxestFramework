#ifndef SAMPLES_HLSL
#define SAMPLES_HLSL


// depends on:
// #include "math.hlsl"


static float2 vogelDiskOffsets8[8] =
{
	float2(0.25f, 0.0f),
	float2(-0.319301f, 0.292484f),
	float2(0.0489135f, -0.556873f),
	float2(0.402386f, 0.524962f),
	float2(-0.738516f, -0.130745f),
	float2(0.699687f, -0.444903f),
	float2(-0.234197f, 0.870432f),
	float2(-0.446049f, -0.859384f),
};


static float2 vogelDiskOffsets16[16] =
{
	float2(0.176777f, 0.0f),
	float2(-0.22578f, 0.206818f),
	float2(0.0345871f, -0.393769f),
	float2(0.28453f, 0.371204f),
	float2(-0.52221f, -0.0924509f),
	float2(0.494753f, -0.314594f),
	float2(-0.165602f, 0.615488f),
	float2(-0.315404f, -0.607676f),
	float2(0.684568f, 0.250232f),
	float2(-0.712353f, 0.293773f),
	float2(0.343624f, -0.733602f),
	float2(0.253402f, 0.809035f),
	float2(-0.76455f, -0.443524f),
	float2(0.897228f, -0.196803f),
	float2(-0.547909f, 0.778489f),
	float2(-0.125948f, -0.976159f),
};


static float2 vogelDiskOffsets32[32] =
{
	float2(0.125f, 0.0f),
	float2(-0.15965f, 0.146242f),
	float2(0.0244568f, -0.278436f),
	float2(0.201193f, 0.262481f),
	float2(-0.369258f, -0.0653727f),
	float2(0.349843f, -0.222451f),
	float2(-0.117098f, 0.435216f),
	float2(-0.223025f, -0.429692f),
	float2(0.484063f, 0.176941f),
	float2(-0.50371f, 0.207729f),
	float2(0.242979f, -0.518735f),
	float2(0.179182f, 0.572074f),
	float2(-0.540618f, -0.313619f),
	float2(0.634436f, -0.139161f),
	float2(-0.387431f, 0.550475f),
	float2(-0.089059f, -0.690249f),
	float2(0.548799f, 0.463082f),
	float2(-0.738898f, 0.0300908f),
	float2(0.53931f, -0.535975f),
	float2(-0.0366048f, 0.779766f),
	float2(-0.512366f, -0.614904f),
	float2(0.812275f, 0.10993f),
	float2(-0.688699f, 0.47835f),
	float2(0.188794f, -0.835902f),
	float2(0.434361f, 0.759576f),
	float2(-0.850198f, -0.272101f),
	float2(0.826468f, -0.380889f),
	float2(-0.35874f, 0.854799f),
	float2(-0.318489f, -0.888364f),
	float2(0.849429f, 0.447599f),
	float2(-0.944309f, 0.247803f),
	float2(0.537548f, -0.833917f),
};


static float2 vogelDiskOffsets64[64] =
{
	float2(0.0883883f, 0.0f),
	float2(-0.11289f, 0.103409f),
	float2(0.0172935f, -0.196884f),
	float2(0.142265f, 0.185602f),
	float2(-0.261105f, -0.0462255f),
	float2(0.247377f, -0.157297f),
	float2(-0.082801f, 0.307744f),
	float2(-0.157702f, -0.303838f),
	float2(0.342284f, 0.125116f),
	float2(-0.356177f, 0.146886f),
	float2(0.171812f, -0.366801f),
	float2(0.126701f, 0.404517f),
	float2(-0.382275f, -0.221762f),
	float2(0.448614f, -0.0984014f),
	float2(-0.273955f, 0.389245f),
	float2(-0.0629742f, -0.48808f),
	float2(0.388059f, 0.327448f),
	float2(-0.522479f, 0.0212774f),
	float2(0.38135f, -0.378992f),
	float2(-0.0258835f, 0.551378f),
	float2(-0.362297f, -0.434803f),
	float2(0.574365f, 0.0777325f),
	float2(-0.486984f, 0.338244f),
	float2(0.133497f, -0.591072f),
	float2(0.30714f, 0.537101f),
	float2(-0.60118f, -0.192405f),
	float2(0.584401f, -0.269329f),
	float2(-0.253667f, 0.604434f),
	float2(-0.225206f, -0.628168f),
	float2(0.600637f, 0.316501f),
	float2(-0.667727f, 0.175223f),
	float2(0.380104f, -0.589668f),
	float2(0.11987f, 0.702455f),
	float2(-0.571468f, -0.443691f),
	float2(0.731777f, -0.0597007f),
	float2(-0.506463f, 0.546061f),
	float2(0.00468483f, -0.755176f),
	float2(0.513531f, 0.567647f),
	float2(-0.772194f, -0.0726587f),
	float2(0.626471f, -0.474049f),
	float2(-0.143532f, 0.782439f),
	float2(-0.427855f, -0.682186f),
	float2(0.785586f, 0.216604f),
	float2(-0.734081f, 0.375249f),
	float2(0.291131f, -0.78138f),
	float2(0.316613f, 0.781469f),
	float2(-0.769645f, -0.366346f),
	float2(0.823702f, -0.252395f),
	float2(-0.441485f, 0.750269f),
	float2(-0.183088f, -0.860184f),
	float2(0.723226f, 0.515758f),
	float2(-0.890364f, 0.109268f),
	float2(0.588374f, -0.68857f),
	float2(0.031535f, 0.913752f),
	float2(-0.646417f, -0.658565f),
	float2(0.929916f, 0.049433f),
	float2(-0.725559f, 0.596972f),
	float2(0.132945f, -0.93849f),
	float2(0.540515f, 0.78861f),
	float2(-0.939176f, -0.218255f),
	float2(0.846992f, -0.477406f),
	float2(-0.304591f, 0.931752f),
	float2(-0.408044f, -0.900035f),
	float2(0.916067f, 0.391162f),
};


static float2 alchemySpiralOffsets8[8] =
{
	float2(-0.92388f, 0.382683f),
	float2(-0.382684f, 0.923879f),
	float2(0.382683f, 0.92388f),
	float2(0.923879f, 0.382684f),
	float2(0.92388f, -0.382682f),
	float2(0.382685f, -0.923879f),
	float2(-0.382681f, -0.92388f),
	float2(-0.923879f, -0.382686f),
};


static float2 alchemySpiralOffsets16[16] =
{
	float2(0.19509f, 0.980785f),
	float2(-0.55557f, -0.83147f),
	float2(0.831469f, 0.555571f),
	float2(-0.980785f, -0.195091f),
	float2(0.980785f, -0.19509f),
	float2(-0.83147f, 0.555569f),
	float2(0.555571f, -0.831469f),
	float2(-0.195092f, 0.980785f),
	float2(-0.195089f, -0.980786f),
	float2(0.555569f, 0.83147f),
	float2(-0.831469f, -0.555572f),
	float2(0.980785f, 0.195092f),
	float2(-0.980786f, 0.195088f),
	float2(0.831471f, -0.555568f),
	float2(-0.555572f, 0.831468f),
	float2(0.195093f, -0.980785f),
};


static float2 alchemySpiralOffsets32[32] =
{
	float2(0.77301f, 0.634393f),
	float2(-0.471397f, 0.881921f),
	float2(-0.95694f, -0.290285f),
	float2(0.0980174f, -0.995185f),
	float2(0.995185f, -0.0980168f),
	float2(0.290284f, 0.95694f),
	float2(-0.881922f, 0.471396f),
	float2(-0.634393f, -0.773011f),
	float2(0.634394f, -0.77301f),
	float2(0.881921f, 0.471397f),
	float2(-0.290285f, 0.95694f),
	float2(-0.995185f, -0.0980181f),
	float2(-0.0980161f, -0.995185f),
	float2(0.956941f, -0.290284f),
	float2(0.471396f, 0.881922f),
	float2(-0.773011f, 0.634392f),
	float2(-0.77301f, -0.634394f),
	float2(0.471398f, -0.881921f),
	float2(0.95694f, 0.290286f),
	float2(-0.0980188f, 0.995185f),
	float2(-0.995185f, 0.0980154f),
	float2(-0.290283f, -0.956941f),
	float2(0.881922f, -0.471395f),
	float2(0.634393f, 0.77301f),
	float2(-0.634396f, 0.773008f),
	float2(-0.881921f, -0.471397f),
	float2(0.290289f, -0.956939f),
	float2(0.995185f, 0.0980175f),
	float2(0.0980129f, 0.995185f),
	float2(-0.95694f, 0.290284f),
	float2(-0.471393f, -0.881923f),
	float2(0.773011f, -0.634393f),
};


static float2 alchemySpiralOffsets64[64] =
{
	float2(0.941544f, 0.33689f),
	float2(0.514103f, 0.857729f),
	float2(-0.146731f, 0.989177f),
	float2(-0.740951f, 0.671559f),
	float2(-0.998795f, 0.0490675f),
	float2(-0.803207f, -0.595699f),
	float2(-0.24298f, -0.970031f),
	float2(0.427555f, -0.903989f),
	float2(0.903989f, -0.427555f),
	float2(0.970031f, 0.242981f),
	float2(0.595699f, 0.803208f),
	float2(-0.0490681f, 0.998795f),
	float2(-0.671559f, 0.740951f),
	float2(-0.989177f, 0.14673f),
	float2(-0.857728f, -0.514103f),
	float2(-0.336889f, -0.941544f),
	float2(0.33689f, -0.941544f),
	float2(0.857729f, -0.514102f),
	float2(0.989176f, 0.146731f),
	float2(0.671558f, 0.740952f),
	float2(0.0490668f, 0.998796f),
	float2(-0.5957f, 0.803207f),
	float2(-0.970031f, 0.242979f),
	float2(-0.903989f, -0.427555f),
	float2(-0.427553f, -0.90399f),
	float2(0.24298f, -0.970031f),
	float2(0.803209f, -0.595698f),
	float2(0.998795f, 0.0490679f),
	float2(0.74095f, 0.671561f),
	float2(0.14673f, 0.989177f),
	float2(-0.514105f, 0.857727f),
	float2(-0.941544f, 0.33689f),
	float2(-0.941543f, -0.336892f),
	float2(-0.514102f, -0.857729f),
	float2(0.146733f, -0.989176f),
	float2(0.740951f, -0.671559f),
	float2(0.998796f, -0.0490652f),
	float2(0.803207f, 0.5957f),
	float2(0.242978f, 0.970032f),
	float2(-0.427556f, 0.903989f),
	float2(-0.90399f, 0.427553f),
	float2(-0.970031f, -0.242981f),
	float2(-0.595697f, -0.803209f),
	float2(0.0490685f, -0.998795f),
	float2(0.671561f, -0.740949f),
	float2(0.989177f, -0.14673f),
	float2(0.857727f, 0.514105f),
	float2(0.336889f, 0.941544f),
	float2(-0.336893f, 0.941543f),
	float2(-0.857729f, 0.514102f),
	float2(-0.989176f, -0.146733f),
	float2(-0.671558f, -0.740952f),
	float2(-0.0490645f, -0.998796f),
	float2(0.5957f, -0.803207f),
	float2(0.970032f, -0.242977f),
	float2(0.903989f, 0.427556f),
	float2(0.427552f, 0.903991f),
	float2(-0.242982f, 0.970031f),
	float2(-0.80321f, 0.595697f),
	float2(-0.998795f, -0.0490692f),
	float2(-0.740949f, -0.671562f),
	float2(-0.146729f, -0.989177f),
	float2(0.514106f, -0.857727f),
	float2(0.941545f, -0.336888f),
};


float2 VogelDiskOffset(int sampleIndex, int samplesCount, float phi)
{
	float r = sqrt(sampleIndex + 0.5f) / sqrt(samplesCount);
	float theta = sampleIndex*GoldenAngle + phi;

	float sine, cosine;
	sincos(theta, sine, cosine);
	
	return float2(r * cosine, r * sine);
}


float2 AlchemySpiralOffset(int sampleIndex, int samplesCount, float phi)
{
	float alpha = float(sampleIndex + 0.5f) / samplesCount;
	float theta = 7.0f*TwoPi*alpha + phi;

	float sine, cosine;
	sincos(theta, sine, cosine);
	
	return float2(cosine, sine);
}


#endif