#include <Novice.h>
#include <cmath>

const char kWindowTitle[] = "GC2D_02_アリミズ_ユウタ_タイトル";

struct Vector3 {
    float x, y, z;
};

struct Matrix4x4 {
    float m[4][4];
};

Matrix4x4 Multiply(const Matrix4x4& a, const Matrix4x4& b) {
    Matrix4x4 result = {};
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            result.m[y][x] = 0;
            for (int k = 0; k < 4; k++) {
                result.m[y][x] += a.m[y][k] * b.m[k][x];
            }
        }
    }
    return result;
}


Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
    float cx = cosf(rotate.x), sx = sinf(rotate.x);
    float cy = cosf(rotate.y), sy = sinf(rotate.y);
    float cz = cosf(rotate.z), sz = sinf(rotate.z);

    Matrix4x4 rotX = {
        1, 0, 0, 0,
        0, cx, -sx, 0,
        0, sx, cx, 0,
        0, 0, 0, 1
    };

    Matrix4x4 rotY = {
        cy, 0, sy, 0,
        0, 1, 0, 0,
        -sy, 0, cy, 0,
        0, 0, 0, 1
    };

    Matrix4x4 rotZ = {
        cz, -sz, 0, 0,
        sz, cz, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };

    Matrix4x4 scaleM = {
        scale.x, 0, 0, 0,
        0, scale.y, 0, 0,
        0, 0, scale.z, 0,
        0, 0, 0, 1
    };

    Matrix4x4 transM = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        translate.x, translate.y, translate.z, 1
    };

    Matrix4x4 result = Multiply(scaleM, Multiply(rotZ, Multiply(rotY, Multiply(rotX, transM))));
    return result;
}


void MatrixScreenPrintf(int x, int y, const Matrix4x4& mat, const char* label) {
    Novice::ScreenPrintf(x, y, "%s", label);
    for (int row = 0; row < 4; ++row) {
        Novice::ScreenPrintf(x, y + 20 * (row + 1),
            "%6.2f %6.2f %6.2f %6.2f",
            mat.m[row][0], mat.m[row][1], mat.m[row][2], mat.m[row][3]);
    }
}

// Windowsアプリのエントリーポイント
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    Novice::Initialize(kWindowTitle, 1280, 720);

    char keys[256] = { 0 };
    char preKeys[256] = { 0 };


    Vector3 scale{ 1.2f, 0.79f, -2.1f };
    Vector3 rotate{ 0.4f, 1.43f, -0.8f };
    Vector3 translate{ 2.7f, -4.15f, 1.57f };

    Matrix4x4 worldMatrix = MakeAffineMatrix(scale, rotate, translate);

    while (Novice::ProcessMessage() == 0) {
        Novice::BeginFrame();

        memcpy(preKeys, keys, 256);
        Novice::GetHitKeyStateAll(keys);

        /// 描画処理
        MatrixScreenPrintf(0, 0, worldMatrix, "worldMatrix");

        Novice::EndFrame();

        if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
            break;
        }
    }

    Novice::Finalize();
    return 0;
}
