#ifndef _DIRECT3D8TO9TYPES_H_
#define _DIRECT3D8TO9TYPES_H_

#include <float.h>

#if _MSC_VER >= 1200
#pragma warning(push)
#endif
#pragma warning(disable:4201) // anonymous unions warning
#if defined(_X86_) || defined(_IA64_)
#pragma pack(4)
#endif

typedef struct _D3DVIEWPORT8 {
    DWORD       X;
    DWORD       Y;            /* Viewport Top left */
    DWORD       Width;
    DWORD       Height;       /* Viewport Dimensions */
    float       MinZ;         /* Min/max of clip Volume */
    float       MaxZ;
} D3DVIEWPORT8;

typedef struct _D3DMATERIAL8 {
    D3DCOLORVALUE   Diffuse;        /* Diffuse color RGBA */
    D3DCOLORVALUE   Ambient;        /* Ambient color RGB */
    D3DCOLORVALUE   Specular;       /* Specular 'shininess' */
    D3DCOLORVALUE   Emissive;       /* Emissive color RGB */
    float           Power;          /* Sharpness if specular highlight */
} D3DMATERIAL8;

typedef struct _D3DLIGHT8 {
    D3DLIGHTTYPE    Type;            /* Type of light source */
    D3DCOLORVALUE   Diffuse;         /* Diffuse color of light */
    D3DCOLORVALUE   Specular;        /* Specular color of light */
    D3DCOLORVALUE   Ambient;         /* Ambient color of light */
    D3DVECTOR       Position;         /* Position in world space */
    D3DVECTOR       Direction;        /* Direction in world space */
    float           Range;            /* Cutoff range */
    float           Falloff;          /* Falloff */
    float           Attenuation0;     /* Constant attenuation */
    float           Attenuation1;     /* Linear attenuation */
    float           Attenuation2;     /* Quadratic attenuation */
    float           Theta;            /* Inner angle of spotlight cone */
    float           Phi;              /* Outer angle of spotlight cone */
} D3DLIGHT8;

typedef struct _D3DCLIPSTATUS8 {
    DWORD ClipUnion;
    DWORD ClipIntersection;
} D3DCLIPSTATUS8;

/* Resize Optional Parameters */
typedef struct _D3D8PRESENT_PARAMETERS_
{
    UINT                BackBufferWidth;
    UINT                BackBufferHeight;
    D3DFORMAT           BackBufferFormat;
    UINT                BackBufferCount;

    D3DMULTISAMPLE_TYPE MultiSampleType;

    D3DSWAPEFFECT       SwapEffect;
    HWND                hDeviceWindow;
    BOOL                Windowed;
    BOOL                EnableAutoDepthStencil;
    D3DFORMAT           AutoDepthStencilFormat;
    DWORD               Flags;

    /* Following elements must be zero for Windowed mode */
    UINT                FullScreen_RefreshRateInHz;
    UINT                FullScreen_PresentationInterval;

} D3D8PRESENT_PARAMETERS;


/* Surface Description */
typedef struct _D3D8SURFACE_DESC
{
    D3DFORMAT           Format;
    D3DRESOURCETYPE     Type;
    DWORD               Usage;
    D3DPOOL             Pool;
    UINT                Size;

    D3DMULTISAMPLE_TYPE MultiSampleType;
    UINT                Width;
    UINT                Height;
} D3D8SURFACE_DESC;

typedef struct _D3D8VOLUME_DESC
{
    D3DFORMAT           Format;
    D3DRESOURCETYPE     Type;
    DWORD               Usage;
    D3DPOOL             Pool;
    UINT                Size;

    UINT                Width;
    UINT                Height;
    UINT                Depth;
} D3D8VOLUME_DESC;

#define MAX_DEVICE_IDENTIFIER_STRING        512
typedef struct _D3DADAPTER_IDENTIFIER8
{
    char            Driver[MAX_DEVICE_IDENTIFIER_STRING];
    char            Description[MAX_DEVICE_IDENTIFIER_STRING];

#ifdef _WIN32
    LARGE_INTEGER   DriverVersion;            /* Defined for 32 bit components */
#else
    DWORD           DriverVersionLowPart;     /* Defined for 16 bit driver components */
    DWORD           DriverVersionHighPart;
#endif

    DWORD           VendorId;
    DWORD           DeviceId;
    DWORD           SubSysId;
    DWORD           Revision;

    GUID            DeviceIdentifier;

    DWORD           WHQLLevel;

} D3DADAPTER_IDENTIFIER8;

typedef enum _D3D8TEXTURESTAGESTATETYPE
{
    D3D8TSS_COLOROP        =  1, /* D3DTEXTUREOP - per-stage blending controls for color channels */
    D3D8TSS_COLORARG1      =  2, /* D3DTA_* (texture arg) */
    D3D8TSS_COLORARG2      =  3, /* D3DTA_* (texture arg) */
    D3D8TSS_ALPHAOP        =  4, /* D3DTEXTUREOP - per-stage blending controls for alpha channel */
    D3D8TSS_ALPHAARG1      =  5, /* D3DTA_* (texture arg) */
    D3D8TSS_ALPHAARG2      =  6, /* D3DTA_* (texture arg) */
    D3D8TSS_BUMPENVMAT00   =  7, /* float (bump mapping matrix) */
    D3D8TSS_BUMPENVMAT01   =  8, /* float (bump mapping matrix) */
    D3D8TSS_BUMPENVMAT10   =  9, /* float (bump mapping matrix) */
    D3D8TSS_BUMPENVMAT11   = 10, /* float (bump mapping matrix) */
    D3D8TSS_TEXCOORDINDEX  = 11, /* identifies which set of texture coordinates index this texture */
    D3D8TSS_ADDRESSU       = 13, /* D3DTEXTUREADDRESS for U coordinate */
    D3D8TSS_ADDRESSV       = 14, /* D3DTEXTUREADDRESS for V coordinate */
    D3D8TSS_BORDERCOLOR    = 15, /* D3DCOLOR */
    D3D8TSS_MAGFILTER      = 16, /* D3DTEXTUREFILTER filter to use for magnification */
    D3D8TSS_MINFILTER      = 17, /* D3DTEXTUREFILTER filter to use for minification */
    D3D8TSS_MIPFILTER      = 18, /* D3DTEXTUREFILTER filter to use between mipmaps during minification */
    D3D8TSS_MIPMAPLODBIAS  = 19, /* float Mipmap LOD bias */
    D3D8TSS_MAXMIPLEVEL    = 20, /* DWORD 0..(n-1) LOD index of largest map to use (0 == largest) */
    D3D8TSS_MAXANISOTROPY  = 21, /* DWORD maximum anisotropy */
    D3D8TSS_BUMPENVLSCALE  = 22, /* float scale for bump map luminance */
    D3D8TSS_BUMPENVLOFFSET = 23, /* float offset for bump map luminance */
    D3D8TSS_TEXTURETRANSFORMFLAGS = 24, /* D3DTEXTURETRANSFORMFLAGS controls texture transform */
    D3D8TSS_ADDRESSW       = 25, /* D3DTEXTUREADDRESS for W coordinate */
    D3D8TSS_COLORARG0      = 26, /* D3DTA_* third arg for triadic ops */
    D3D8TSS_ALPHAARG0      = 27, /* D3DTA_* third arg for triadic ops */
    D3D8TSS_RESULTARG      = 28, /* D3DTA_* arg for result (CURRENT or TEMP) */
    D3D8TSS_FORCE_DWORD   = 0x7fffffff, /* force 32-bit size enum */
} D3D8TEXTURESTAGESTATETYPE;

#define D3DCLIPSTATUS8 D3DCLIPSTATUS9
#define D3DMATERIAL8 D3DMATERIAL9
#define D3DVIEWPORT8 D3DVIEWPORT9
#define D3DLIGHT8 D3DLIGHT9

#pragma pack()
#if _MSC_VER >= 1200
#pragma warning(pop)
#else
#pragma warning(default:4201)
#endif

#endif
