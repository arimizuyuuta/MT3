#include <Novice.h>
#include <cmath>   
#include <cstring> 

const char kWindowTitle[] = "GC2D_02_アリミズ_ユウタ_タイトル";

// 行列構造体（4x4）
struct Matrix4x4 {
    float m[4][4];
};

// 正射影行列の作成
Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip) {
    Matrix4x4 mat = {};
    mat.m[0][0] = 2.0f / (right - left);
    mat.m[1][1] = 2.0f / (top - bottom);
    mat.m[2][2] = 1.0f / (farClip - nearClip);
    mat.m[3][0] = -(right + left) / (right - left);
    mat.m[3][1] = -(top + bottom) / (top - bottom);
    mat.m[3][2] = -nearClip / (farClip - nearClip);
    mat.m[3][3] = 1.0f;
    return mat;
}

// 透視射影行列の作成
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip) {
    Matrix4x4 mat = {};
    float f = 1.0f / tanf(fovY / 2.0f);
    mat.m[0][0] = f / aspectRatio;
    mat.m[1][1] = f;
    mat.m[2][2] = farClip / (farClip - nearClip);
    mat.m[2][3] = 1.0f;
    mat.m[3][2] = -nearClip * farClip / (farClip - nearClip);
    return mat;
}

// ビューポート変換行列の作成
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth) {
    Matrix4x4 mat = {};
    mat.m[0][0] = width / 2.0f;
    mat.m[1][1] = -height / 2.0f;
    mat.m[2][2] = maxDepth - minDepth;
    mat.m[3][0] = left + width / 2.0f;
    mat.m[3][1] = top + height / 2.0f;
    mat.m[3][2] = minDepth;
    mat.m[3][3] = 1.0f;
    return mat;
}

// 行列を画面に表示
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {
    Novice::ScreenPrintf(x, y, "%s", label);
    for (int row = 0; row < 4; ++row) {
        Novice::ScreenPrintf(x, y + 20 + row * 20,
            "%6.2f %6.2f %6.2f %6.2f",
            matrix.m[row][0], matrix.m[row][1], matrix.m[row][2], matrix.m[row][3]);
    }
}

// エントリーポイント
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    Novice::Initialize(kWindowTitle, 1280, 720);

    char keys[256] = { 0 };
    char preKeys[256] = { 0 };

    // 各種行列の生成
    Matrix4x4 orthographicMatrix = MakeOrthographicMatrix(-160.f, 160.f, 200.f, 300.f, 0.0f, 1000.0f);
    Matrix4x4 perspectiveFovMatrix = MakePerspectiveFovMatrix(0.63f, 1.33f, 0.1f, 1000.0f);
    Matrix4x4 viewportMatrix = MakeViewportMatrix(100.0f, 200.0f, 600.0f, 300.0f, 0.0f, 1.0f);

    while (Novice::ProcessMessage() == 0) {
        Novice::BeginFrame();

        memcpy(preKeys, keys, 256);
        Novice::GetHitKeyStateAll(keys);

        // 描画処理
        MatrixScreenPrintf(0, 0, orthographicMatrix, "orthographicMatrix");
        MatrixScreenPrintf(0, 120, perspectiveFovMatrix, "perspectiveFovMatrix");
        MatrixScreenPrintf(0, 240, viewportMatrix, "viewportMatrix");

        Novice::EndFrame();

        if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
            break;
        }
    }

    Novice::Finalize();
    return 0;
}
