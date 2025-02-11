#pragma once

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#pragma pack(push, 1)
inline float u_P(float v)
{
    return v;
}

inline float u_P(s16 v)
{
    return float(v) / (32767.f / 12.f);
}

inline void q_P(float& dst, float val)
{
    dst = val;
}

inline void q_P(s16& dst, float val)
{
    dst = u16(clampr<int>(iFloor(val * (32767.f / 12.f)), -32768, 32767));
}

inline u8 q_N(float v)
{
    int _v = clampr(iFloor((v + 1.f) * 127.5f), 0, 255);
    return u8(_v);
}

inline void q_tc(float& dst, float val)
{
    dst = val;
}

inline void q_tc(s16& dst, float val)
{
    dst = s16(clampr<int>(iFloor(val * (32767.f / 16.f)), -32768, 32767));
}

#ifdef _DEBUG
float errN(Fvector3 v, u8* qv)
{
    Fvector3 uv;
    uv.set(float(qv[0]), float(qv[1]), float(qv[2])).div(255.f).mul(2.f).sub(1.f);
    uv.normalize();
    return v.dotproduct(uv);
}
#else
inline float errN(Fvector3 /*v*/, u8* /*qv*/)
{
    return 0;
}
#endif

#pragma region 1W
static VertexElement dwDecl_01W[] = // 24bytes
{
    {0, 0, D3DDECLTYPE_SHORT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0}, // P : 2 : -12..+12
    {0, 8, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0}, // N, w=index(RC, 0..1) : 1 : -1..+1
    {0, 12, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT, 0}, // T : 1 : -1..+1
    {0, 16, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0}, // B : 1 : -1..+1
    {0, 20, D3DDECLTYPE_SHORT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0}, // tc : 1 : -16..+16
    D3DDECL_END()
};

static VertexElement dwDecl_01W_HQ[] = // 36bytes
{
    {0, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0}, // P : 2 : -12..+12
    {0, 16, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0}, // N, w=index(RC, 0..1) : 1 : -1..+1
    {0, 20, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT, 0}, // T : 1 : -1..+1
    {0, 24, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0}, // B : 1 : -1..+1
    {0, 28, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0}, // tc : 1 : -16..+16
    D3DDECL_END()
};
#pragma endregion 1W

#pragma region 2W
static VertexElement dwDecl_2W[] = // 28bytes
{
    {0, 0, D3DDECLTYPE_SHORT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0}, // p : 2 : -12..+12
    // n.xyz, w=weight : 1 : -1..+1, w=0..1
    {0, 8, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
    {0, 12, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT, 0}, // T : 1 : -1..+1
    {0, 16, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0}, // B : 1 : -1..+1
    // xy(tc), zw(indices): 2 : -16..+16, zw[0..32767]
    {0, 20, D3DDECLTYPE_SHORT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
    D3DDECL_END()
};

static VertexElement dwDecl_2W_HQ[] = // 44bytes
{
    {0, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0}, // p : 2 : -12..+12
    // n.xyz, w=weight : 1 : -1..+1, w=0..1
    {0, 16, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
    {0, 20, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT, 0}, // T : 1 : -1..+1
    {0, 24, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0}, // B : 1 : -1..+1
    // xy(tc), zw(indices): 2 : -16..+16, zw[0..32767]
    {0, 28, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
    D3DDECL_END()
};
#pragma endregion 2W

#pragma region 3W
static VertexElement dwDecl_3W[] = // 28bytes
{
    {0, 0, D3DDECLTYPE_SHORT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0}, // p : 2 : -12..+12
    // n.xyz, w=weight0 : 1 : -1..+1, w=0..1
    {0, 8, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
    // T.xyz, w=weight1 : 1 : -1..+1, w=0..1
    {0, 12, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT, 0},
    // B.xyz, w=index2 : 1 : -1..+1, w=0..255
    {0, 16, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0},
    // xy(tc), zw(indices): 2 : -16..+16, zw[0..32767]
    {0, 20, D3DDECLTYPE_SHORT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
    D3DDECL_END()
};

static VertexElement dwDecl_3W_HQ[] = // 44bytes
{
    {0, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0}, // p : 2 : -12..+12
    // n.xyz, w=weight0 : 1 : -1..+1, w=0..1
    {0, 16, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
    // T.xyz, w=weight1 : 1 : -1..+1, w=0..1
    {0, 20, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT, 0},
    // B.xyz, w=index2 : 1 : -1..+1, w=0..255
    {0, 24, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0},
    // xy(tc), zw(indices): 2 : -16..+16, zw[0..32767]
    {0, 28, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
    D3DDECL_END()
};
#pragma endregion 3W

#pragma region 4W
static VertexElement dwDecl_4W[] = // 28bytes
{
    // p : 2 : -12..+12
    {0, 0, D3DDECLTYPE_SHORT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
    // n.xyz, w = weight0 : 1 : -1..+1, w=0..1
    {0, 8, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
    // T.xyz, w = weight1 : 1 : -1..+1, w=0..1
    {0, 12, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT, 0},
    // B.xyz, w = weight2 : 1 : -1..+1, w=0..1
    {0, 16, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0},
    {0, 20, D3DDECLTYPE_SHORT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0}, // : xy(tc) : 2 : -16..+16
    {0, 24, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1}, // : indices : 1 :  0..255
    D3DDECL_END()
};

static VertexElement dwDecl_4W_HQ[] = // 40bytes
{
    // p : 2 : -12..+12
    {0, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
    // n.xyz, w = weight0 : 1 : -1..+1, w=0..1
    {0, 16, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
    // T.xyz, w = weight1 : 1 : -1..+1, w=0..1
    {0, 20, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT, 0},
    // B.xyz, w = weight2 : 1 : -1..+1, w=0..1
    {0, 24, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0},
    {0, 28, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0}, // : xy(tc) : 2 : -16..+16
    {0, 36, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1}, // : indices : 1 :  0..255
    D3DDECL_END()
};
#pragma endregion 4W

template <typename TVal>
struct vertHW_1W
{
    static_assert(std::is_same_v<TVal, float> || std::is_same_v<TVal, s16>, "Only float and s16 are supported");

    TVal Position[4];
    u32 Normal_and_index;
    u32 Tangent;
    u32 Binormal;
    TVal TexCoord[2];

    void set(const Fvector3& position, Fvector3 normal, Fvector3 tangent, Fvector3 binormal, const Fvector2& texcoord, int index)
    {
        normal.normalize_safe();
        tangent.normalize_safe();
        binormal.normalize_safe();
        q_P(Position[0], position.x);
        q_P(Position[1], position.y);
        q_P(Position[2], position.z);
        Position[3] = TVal(1);
        Normal_and_index = color_rgba(q_N(normal.x), q_N(normal.y), q_N(normal.z), u8(index));
        Tangent = color_rgba(q_N(tangent.x), q_N(tangent.y), q_N(tangent.z), 0);
        Binormal = color_rgba(q_N(binormal.x), q_N(binormal.y), q_N(binormal.z), 0);
        q_tc(TexCoord[0], texcoord.x);
        q_tc(TexCoord[1], texcoord.y);
    }

    u16 get_bone() const
    {
        return (u16)color_get_A(Normal_and_index) / 3;
    }

    void get_pos_bones(Fvector& p, CKinematics* Parent) const
    {
        const Fmatrix& xform = Parent->LL_GetBoneInstance(get_bone()).mRenderTransform;
        get_pos(p);
        xform.transform_tiny(p);
    }

    void get_pos(Fvector& p) const
    {
        p.x = u_P(Position[0]);
        p.y = u_P(Position[1]);
        p.z = u_P(Position[2]);
    }
};

template <typename TVal>
struct vertHW_2W
{
    static_assert(std::is_same_v<TVal, float> || std::is_same_v<TVal, s16>, "Only float and s16 are supported");

    TVal Position[4];
    u32 Normal_and_w;
    u32 Tangent;
    u32 Binormal;
    TVal TexCoord_and_index[4];

    void set(const Fvector3& position, Fvector3 normal, Fvector3 tangent, Fvector3 binormal, const Fvector2& texcoord,
        int index0, int index1, float w)
    {
        normal.normalize_safe();
        tangent.normalize_safe();
        binormal.normalize_safe();
        q_P(Position[0], position.x);
        q_P(Position[1], position.y);
        q_P(Position[2], position.z);
        Position[3] = TVal(1);
        Normal_and_w = color_rgba(q_N(normal.x), q_N(normal.y), q_N(normal.z), u8(clampr(iFloor(w * 255.f + .5f), 0, 255)));
        Tangent = color_rgba(q_N(tangent.x), q_N(tangent.y), q_N(tangent.z), 0);
        Binormal = color_rgba(q_N(binormal.x), q_N(binormal.y), q_N(binormal.z), 0);
        q_tc(TexCoord_and_index[0], texcoord.x);
        q_tc(TexCoord_and_index[1], texcoord.y);
        TexCoord_and_index[2] = s16(index0);
        TexCoord_and_index[3] = s16(index1);
    }

    float get_weight() const
    {
        return float(color_get_A(Normal_and_w)) / 255.f;
    }

    u16 get_bone(u16 w) const
    {
        return (u16)TexCoord_and_index[w + 2] / 3;
    }

    void get_pos(Fvector& p) const
    {
        p.x = u_P(Position[0]);
        p.y = u_P(Position[1]);
        p.z = u_P(Position[2]);
    }

    void get_pos_bones(Fvector& p, CKinematics* Parent) const
    {
        Fvector P0, P1;
        Fmatrix& xform0 = Parent->LL_GetBoneInstance(get_bone(0)).mRenderTransform;
        Fmatrix& xform1 = Parent->LL_GetBoneInstance(get_bone(1)).mRenderTransform;
        get_pos(P0);
        xform0.transform_tiny(P0);
        get_pos(P1);
        xform1.transform_tiny(P1);
        p.lerp(P0, P1, get_weight());
    }
};

template <typename TVal>
struct vertHW_3W
{
    static_assert(std::is_same_v<TVal, float> || std::is_same_v<TVal, s16>, "Only float and s16 are supported");

    TVal Position[4];
    u32 Normal_and_w;
    u32 Tangent_and_w;
    u32 Binormal_and_index;
    TVal TexCoord_and_index[4];

    void set(const Fvector3& position, Fvector3 normal, Fvector3 tangent, Fvector3 binormal, const Fvector2& texcoord,
        int index0, int index1, int index2,
        float w0, float w1)
    {
        normal.normalize_safe();
        tangent.normalize_safe();
        binormal.normalize_safe();
        q_P(Position[0], position.x);
        q_P(Position[1], position.y);
        q_P(Position[2], position.z);
        Position[3] = TVal(1);
        Normal_and_w = color_rgba(q_N(normal.x), q_N(normal.y), q_N(normal.z), u8(clampr(iFloor(w0 * 255.f + .5f), 0, 255)));
        Tangent_and_w = color_rgba(q_N(tangent.x), q_N(tangent.y), q_N(tangent.z), u8(clampr(iFloor(w1 * 255.f + .5f), 0, 255)));
        Binormal_and_index = color_rgba(q_N(binormal.x), q_N(binormal.y), q_N(binormal.z), u8(index2));
        q_tc(TexCoord_and_index[0], texcoord.x);;
        q_tc(TexCoord_and_index[1], texcoord.y);;
        TexCoord_and_index[2] = s16(index0);
        TexCoord_and_index[3] = s16(index1);
    }

    float get_weight0() const
    {
        return float(color_get_A(Normal_and_w)) / 255.f;
    }

    float get_weight1() const
    {
        return float(color_get_A(Tangent_and_w)) / 255.f;
    }

    u16 get_bone(u16 w) const
    {
        switch (w)
        {
        case 0:
        case 1: return (u16)TexCoord_and_index[w + 2] / 3;
        case 2: return (u16)color_get_A(Binormal_and_index) / 3;
        }
        R_ASSERT(0);
        return 0;
    }

    void get_pos(Fvector& p) const
    {
        p.x = u_P(Position[0]);
        p.y = u_P(Position[1]);
        p.z = u_P(Position[2]);
    }

    void get_pos_bones(Fvector& p, CKinematics* Parent) const
    {
        Fvector P0, P1, P2;
        Fmatrix& xform0 = Parent->LL_GetBoneInstance(get_bone(0)).mRenderTransform;
        Fmatrix& xform1 = Parent->LL_GetBoneInstance(get_bone(1)).mRenderTransform;
        Fmatrix& xform2 = Parent->LL_GetBoneInstance(get_bone(2)).mRenderTransform;
        get_pos(P0);
        xform0.transform_tiny(P0);
        get_pos(P1);
        xform1.transform_tiny(P1);
        get_pos(P2);
        xform2.transform_tiny(P2);
        float w0 = get_weight0();
        float w1 = get_weight1();
        P0.mul(w0);
        P1.mul(w1);
        P2.mul(1 - w0 - w1);
        p = P0;
        p.add(P1);
        p.add(P2);
    }
};

template <typename TVal>
struct vertHW_4W
{
    static_assert(std::is_same_v<TVal, float> || std::is_same_v<TVal, s16>, "Only float and s16 are supported");

    TVal Position[4];
    u32 Normal_and_w;
    u32 Tangent_and_w;
    u32 Binormal_and_w;
    TVal TexCoord[2];
    u32 Index;

    void set(const Fvector3& position, Fvector3 normal, Fvector3 tangent, Fvector3 binormal, const Fvector2& texcoord,
        int index0, int index1, int index2, int index3,
        float w0, float w1, float w2)
    {
        normal.normalize_safe();
        tangent.normalize_safe();
        binormal.normalize_safe();
        q_P(Position[0], position.x);
        q_P(Position[1], position.y);
        q_P(Position[2], position.z);
        Position[3] = TVal(1);
        Normal_and_w = color_rgba(q_N(normal.x), q_N(normal.y), q_N(normal.z), u8(clampr(iFloor(w0 * 255.f + .5f), 0, 255)));
        Tangent_and_w = color_rgba(q_N(tangent.x), q_N(tangent.y), q_N(tangent.z), u8(clampr(iFloor(w1 * 255.f + .5f), 0, 255)));
        Binormal_and_w = color_rgba(q_N(binormal.x), q_N(binormal.y), q_N(binormal.z), u8(clampr(iFloor(w2 * 255.f + .5f), 0, 255)));
        q_tc(TexCoord[0], texcoord.x);
        q_tc(TexCoord[1], texcoord.y);
        Index = color_rgba(u8(index0), u8(index1), u8(index2), u8(index3));
    }

    float get_weight0() const
    {
        return float(color_get_A(Normal_and_w)) / 255.f;
    }

    float get_weight1() const
    {
        return float(color_get_A(Tangent_and_w)) / 255.f;
    }

    float get_weight2() const
    {
        return float(color_get_A(Binormal_and_w)) / 255.f;
    }

    u16 get_bone(u16 w) const
    {
        switch (w)
        {
        case 0: return (u16)color_get_R(Index) / 3;
        case 1: return (u16)color_get_G(Index) / 3;
        case 2: return (u16)color_get_B(Index) / 3;
        case 3: return (u16)color_get_A(Index) / 3;
        }
        R_ASSERT(0);
        return 0;
    }

    void get_pos(Fvector& p) const
    {
        p.x = u_P(Position[0]);
        p.y = u_P(Position[1]);
        p.z = u_P(Position[2]);
    }

    void get_pos_bones(Fvector& p, CKinematics* Parent) const
    {
        Fvector P[4];
        for (u16 i = 0; i < 4; ++i)
        {
            Fmatrix& xform = Parent->LL_GetBoneInstance(get_bone(i)).mRenderTransform;
            get_pos(P[i]);
            xform.transform_tiny(P[i]);
        }

        float w[3];
        w[0] = get_weight0();
        w[1] = get_weight1();
        w[2] = get_weight2();

        for (int j = 0; j < 3; ++j)
            P[j].mul(w[j]);
        P[3].mul(1 - w[0] - w[1] - w[2]);

        p = P[0];
        for (int k = 1; k < 4; ++k)
            p.add(P[k]);
    }
};

template <typename T>
constexpr VertexElement* get_decl() = delete;

template <>
constexpr VertexElement* get_decl<vertHW_1W<s16>>()
{
    return dwDecl_01W;
}

template <>
constexpr VertexElement* get_decl<vertHW_2W<s16>>()
{
    return dwDecl_2W;
}

template <>
constexpr VertexElement* get_decl<vertHW_3W<s16>>()
{
    return dwDecl_3W;
}

template <>
constexpr VertexElement* get_decl<vertHW_4W<s16>>()
{
    return dwDecl_4W;
}

template <>
constexpr VertexElement* get_decl<vertHW_1W<float>>()
{
    return dwDecl_01W_HQ;
}

template <>
constexpr VertexElement* get_decl<vertHW_2W<float>>()
{
    return dwDecl_2W_HQ;
}

template <>
constexpr VertexElement* get_decl<vertHW_3W<float>>()
{
    return dwDecl_3W_HQ;
}

template <>
constexpr VertexElement* get_decl<vertHW_4W<float>>()
{
    return dwDecl_4W_HQ;
}
#pragma pack(pop)
