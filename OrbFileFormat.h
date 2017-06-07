#pragma once
//------------------------------------------------------------------------------
/**
    @file OrbFileFormat.h
    @brief Oryol Binary (.orb) file format definition

    ORB file structure:

    1 OrbHeader
    0..N OrbVertexComponent
    0..N OrbValueProperty
    0..N OrbTextureProperty
    0..N OrbMaterial
    0..N OrbMesh
    0..N OrbBone
    0..N OrbNode
    0..N OrbAnimKeyFormat
    0..N OrbAnimCurve
    0..N OrbAnimClip
    VertexData
    IndexData           (padded to multiple of 4)
    AnimData
    StringData
*/

namespace Oryol {

#pragma pack(push,1)
// NOTE: offsets and sizes are in bytes, all offsets and sizes must be 4-byte multiples
struct OrbHeader {
    uint32_t Magic;     // 'ORB1'
    uint32_t VertexComponentOffset;
    uint32_t NumVertexComponents;
    uint32_t ValuePropOffset;
    uint32_t NumValueProps;
    uint32_t TexturePropOffset;
    uint32_t NumTextureProps;
    uint32_t MaterialOffset;
    uint32_t NumMaterials;
    uint32_t MeshOffset;
    uint32_t NumMeshes;
    uint32_t BoneOffset;
    uint32_t NumBones;
    uint32_t NodeOffset;
    uint32_t NumNodes;
    uint32_t AnimKeyComponentOffset;
    uint32_t NumAnimKeyComponents;
    uint32_t AnimCurveOffset;
    uint32_t NumAnimCurves;
    uint32_t AnimClipOffset;
    uint32_t NumAnimClips;
    uint32_t VertexDataOffset;
    uint32_t VertexDataSize;
    uint32_t IndexDataOffset;
    uint32_t IndexDataSize;     // must be multiple of 4
    uint32_t AnimKeyDataOffset;
    uint32_t AnimKeyDataSize;
    uint32_t StringPoolDataOffset;
    uint32_t StringPoolDataSize;
};

struct OrbVertexAttr {
    enum Enum {
        Invalid = 0,
        Position,
        Normal,
        TexCoord0,
        TexCoord1,
        TexCoord2,
        TexCoord3,
        Tangent,
        Binormal,
        Weights,
        Indices,
        Color0,
        Color1,
    };
};

struct OrbVertexFormat {
    enum Enum {
        Invalid = 0,
        Float,
        Float2,
        Float3,
        Float4,
        Byte4,
        Byte4N,
        UByte4,
        UByte4N,
        Short2,
        Short2N,
        Short4,
        Short4N
    };
};

struct OrbVertexComponent {
    uint32_t Attr = OrbVertexAttr::Invalid;
    uint32_t Format = OrbVertexFormat::Invalid;
};

struct OrbValueProperty {
    uint32_t Name;
    uint32_t Dim;       // 1, 2, 3 or 4 
    float Value[4];
};

struct OrbTextureProperty {
    uint32_t Name;
    uint32_t Location;
};

struct OrbMaterial {
    uint32_t Name;
    uint32_t Shader;
    uint32_t FirstValueProp;
    uint32_t NumValueProps;
    uint32_t FirstTextureProp;
    uint32_t NumTextureProps;
};

struct OrbMesh {
    uint32_t Material;
    uint32_t FirstVertex;
    uint32_t NumVertices;
    uint32_t FirstIndex;
    uint32_t NumIndices;
    float Size[3];
};

struct OrbBone {
    uint32_t Name;
    int32_t Parent;
    float Translate[3];
    float Scale[3];
    float Rotate[4];
};

struct OrbNode {
    uint32_t Name;
    int32_t Parent;
    uint32_t FirstMesh;
    uint32_t NumMeshes;
    float Translate[3];
    float Scale[3];
    float Rotate[4];
};

struct OrbAnimKeyFormat {
    enum Enum {
        Invalid = 0,
        Float,
        Float2,
        Float3,
        Float4,
        Quaternion,
    };
};

struct OrbAnimKeyComponent {
    uint32_t KeyFormat;
};

struct OrbAnimCurve {
    int32_t KeyOffset;  // -1 if the curve is statis
    float StaticKey[4];
};

struct OrbAnimClip {
    uint32_t Name;
    float KeyDuration;
    uint32_t FirstCurve;
    uint32_t NumCurves;
};
#pragma pack(pop) 

} // namespace Oryol
