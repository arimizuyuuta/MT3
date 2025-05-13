#include <Novice.h>
#include <cmath>  

const char kWindowTitle[] = "GC2D_02_アリミズ_ユウタ_タイトル";

struct Matrix4x4 {
    float m[4][4];
};

// X軸回転
Matrix4x4 MakeRotateXMatrix(float radian) {
    return {
        1.0f,        0,         0, 0,
        0,   std::cos(radian), std::sin(radian), 0,
        0,  -std::sin(radian), std::cos(radian), 0,
        0,        0,         0, 1.0f
    };
}

// Y軸回転
Matrix4x4 MakeRotateYMatrix(float radian) {
    return {
        std::cos(radian), 0, -std::sin(radian), 0,
        0,                1,         0,          0,
        std::sin(radian), 0,  std::cos(radian), 0,
        0,                0,         0,          1
    };
}

// Z軸回転
Matrix4x4 MakeRotateZMatrix(float radian) {
    return {
        std::cos(radian), std::sin(radian), 0, 0,
       -std::sin(radian), std::cos(radian), 0, 0,
        0,                0,                1, 0,
        0,                0,                0, 1
    };
}

// 行列の乗算
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
    Matrix4x4 result{};
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.m[i][j] = 0;
            for (int k = 0; k < 4; ++k) {
                result.m[i][j] += m1.m[i][k] * m2.m[k][j];
            }
        }
    }
    return result;
}

// 行列を画面に表示
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {
    const int kRowHeight = 20;
    Novice::ScreenPrintf(x, y, "%s", label);
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            Novice::ScreenPrintf(x + col * 60, y + (row + 1) * kRowHeight, "%.2f", matrix.m[row][col]);
        }
    }
}
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    // ライブラリの初期化
    Novice::Initialize(kWindowTitle, 1280, 720);

    // キー入力結果を受け取る箱
    char keys[256] = { 0 };
    char preKeys[256] = { 0 };

    float x = 0.4f;
    float y = 1.43f;
    float z = -0.8f;

    Matrix4x4 rotateXMatrix = MakeRotateXMatrix(x);
    Matrix4x4 rotateYMatrix = MakeRotateYMatrix(y);
    Matrix4x4 rotateZMatrix = MakeRotateZMatrix(z);
    Matrix4x4 rotateXYZMatrix = Multiply(rotateXMatrix, Multiply(rotateYMatrix, rotateZMatrix));
    // ウィンドウの×ボタンが押されるまでループ
    while (Novice::ProcessMessage() == 0) {
        // フレームの開始
        Novice::BeginFrame();

        // キー入力を受け取る
        memcpy(preKeys, keys, 256);
        Novice::GetHitKeyStateAll(keys);

        ///
        /// ↓更新処理ここから

        ///
        /// ↑更新処理ここまで
        ///

        ///
        /// ↓描画処理ここから
        /// 
        MatrixScreenPrintf(0, 0, rotateXMatrix, "rotateXMatrix");
        MatrixScreenPrintf(0, 5 * 20, rotateYMatrix, "rotateYMatrix");
        MatrixScreenPrintf(0, 5 * 2 * 20, rotateZMatrix, "rotateZMatrix");
        MatrixScreenPrintf(0, 5 * 3 * 20, rotateXYZMatrix, "rotateXYZMatrix");
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
