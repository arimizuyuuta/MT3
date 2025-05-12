#include <Novice.h>
#include <cmath>  

const char kWindowTitle[] = "GC2D_02_アリミズ_ユウタ_タイトル";

struct Vector3 {
    float x, y, z;
};

struct Matrix4x4 {
    float m[4][4];
};

Matrix4x4 MakeTranslateMatrix(const Vector3& translate) {
    Matrix4x4 result = {};
    for (int i = 0; i < 4; ++i) result.m[i][i] = 1.0f;
    result.m[3][0] = translate.x;
    result.m[3][1] = translate.y;
    result.m[3][2] = translate.z;
    return result;
}

Matrix4x4 MakeScaleMatrix(const Vector3& scale) {
    Matrix4x4 result = {};
    result.m[0][0] = scale.x;
    result.m[1][1] = scale.y;
    result.m[2][2] = scale.z;
    result.m[3][3] = 1.0f;
    return result;
}

Vector3 Transform(const Vector3& v, const Matrix4x4& m) {
    Vector3 result;
    result.x = v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0] + m.m[3][0];
    result.y = v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1] + m.m[3][1];
    result.z = v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] + m.m[3][2];
    return result;
}

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {
    Novice::ScreenPrintf(x, y, "%s", label);
    for (int row = 0; row < 4; ++row) {
        Novice::ScreenPrintf(
            x, y + 20 + row * 20,
            "%6.2f %6.2f %6.2f %6.2f",
            matrix.m[row][0], matrix.m[row][1], matrix.m[row][2], matrix.m[row][3]
        );
    }
}
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    // ライブラリの初期化
    Novice::Initialize(kWindowTitle, 1280, 720);

    // キー入力結果を受け取る箱
    char keys[256] = { 0 };
    char preKeys[256] = { 0 };

    
    // ウィンドウの×ボタンが押されるまでループ
    while (Novice::ProcessMessage() == 0) {
        // フレームの開始
        Novice::BeginFrame();

        // キー入力を受け取る
        memcpy(preKeys, keys, 256);
        Novice::GetHitKeyStateAll(keys);

        ///
        /// ↓更新処理ここから
        Vector3 translate = { 4.1f, 2.6f, 0.8f };
        Vector3 scale = { 1.5f, 5.2f, 7.3f };
        Matrix4x4 translateMatrix = MakeTranslateMatrix(translate);
        Matrix4x4 scaleMatrix = MakeScaleMatrix(scale);

        Vector3 point = { 2.3f, 3.8f, 1.4f };
        Matrix4x4 transformMatrix = {
            1.0f, 2.0f, 3.0f, 4.0f,
            3.0f, 1.0f, 1.0f, 2.0f,
            1.0f, 4.0f, 2.0f, 3.0f,
            2.0f, 2.0f, 1.0f, 3.0f
        };

        Vector3 transformed = Transform(point, transformMatrix);
        ///
        /// ↑更新処理ここまで
        ///

        ///
        /// ↓描画処理ここから
        /// 
     
        Novice::ScreenPrintf(0, 0, "%0.2f\t%0.2f\t%0.2f\ttransformed", transformed.x, transformed.y, transformed.z);

        
        MatrixScreenPrintf(0, 20, translateMatrix, "translateMatrix");
        MatrixScreenPrintf(0, 20 + 20 * 5, scaleMatrix, "scaleMatrix"); // 5行下にずらす

        ///
    /// ↑描画処理ここまで
        ///

        // フレームの終了
        Novice::EndFrame();

        // ESCキーが押されたらループを抜ける
        if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
            break;
        }
    }

    // ライブラリの終了
    Novice::Finalize();
    return 0;
}
