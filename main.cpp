#include <Novice.h>
#include <cmath>
#include <cstring>
#include <algorithm> 

const char kWindowTitle[] = "GC2D_02_アリミズ_ユウタ_タイトル";
const int kWindowWidth = 1280;//画面の横幅
const int kWindowHeight = 720;//画面の縦幅

struct Matrix4x4 {
    float m[4][4];
};

// 単位行列
Matrix4x4 MakeIdentity4x4() {
    Matrix4x4 result{};
    for (int i = 0; i < 4; i++) {
        result.m[i][i] = 1.0f;
    }
    return result;
}

// 加算
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2) {
    Matrix4x4 result{};
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            result.m[i][j] = m1.m[i][j] + m2.m[i][j];
    return result;
}

// 減算
Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2) {
    Matrix4x4 result{};
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            result.m[i][j] = m1.m[i][j] - m2.m[i][j];
    return result;
}

// 積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
    Matrix4x4 result{};
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            for (int k = 0; k < 4; k++)
                result.m[i][j] += m1.m[i][k] * m2.m[k][j];
    return result;
}

// 転置
Matrix4x4 Transpose(const Matrix4x4& m) {
    Matrix4x4 result{};
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            result.m[i][j] = m.m[j][i];
    return result;
}

// 逆行列
Matrix4x4 Inverse(const Matrix4x4& m) {
    Matrix4x4 temp = m;
    Matrix4x4 result = MakeIdentity4x4();

    for (int i = 0; i < 4; i++) {
        if (fabsf(temp.m[i][i]) < 1e-6f) {
            bool swapped = false;
            for (int j = i + 1; j < 4; j++) {
                if (fabsf(temp.m[j][i]) > 1e-6f) {
                    std::swap(temp.m[i], temp.m[j]);
                    std::swap(result.m[i], result.m[j]);
                    swapped = true;
                    break;
                }
            }
            if (!swapped) {
                return MakeIdentity4x4(); 
            }
        }

        float pivot = temp.m[i][i];
        for (int j = 0; j < 4; j++) {
            temp.m[i][j] /= pivot;
            result.m[i][j] /= pivot;
        }

        for (int k = 0; k < 4; k++) {
            if (k != i) {
                float factor = temp.m[k][i];
                for (int j = 0; j < 4; j++) {
                    temp.m[k][j] -= temp.m[i][j] * factor;
                    result.m[k][j] -= result.m[i][j] * factor;
                }
            }
        }
    }

    return result;
}

// 行列描画関数
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {
    Novice::ScreenPrintf(x, y - 20, "%s", label);
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            Novice::ScreenPrintf(x + col * 60, y + row * 20, "%6.2f", matrix.m[row][col]);
        }
    }
}


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Matrix4x4 m1 = {
	{{3.2f, 0.7f, 9.6f, 4.4f},
	 {5.5f, 1.3f, 7.8f, 2.1f},
	 {6.9f, 8.0f, 2.6f, 1.0f},
	 {0.5f, 7.2f, 5.1f, 3.3f}}
	};

	Matrix4x4 m2 = {
		{{4.1f, 6.5f, 3.3f, 2.2f},
		 {8.8f, 0.6f, 9.9f, 7.7f},
		 {1.1f, 5.5f, 6.6f, 0.0f},
		 {3.3f, 9.9f, 8.8f, 2.2f}}
	};

	Matrix4x4 resultAdd = Add(m1, m2);
	Matrix4x4 resultSubtract = Subtract(m1, m2);
	Matrix4x4 resultMultiply = Multiply(m1, m2);
	Matrix4x4 inverseM1 = Inverse(m1);
	Matrix4x4 inverseM2 = Inverse(m2);
	Matrix4x4 transposeM1 = Transpose(m1);
	Matrix4x4 transposeM2 = Transpose(m2);
	Matrix4x4 identity = MakeIdentity4x4();

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

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		MatrixScreenPrintf(0, 25, resultAdd, "Add");
		MatrixScreenPrintf(0, 125, resultSubtract, "Subtract");
		MatrixScreenPrintf(0, 225, resultMultiply, "Multiply");
		MatrixScreenPrintf(0, 325, inverseM1, "inverseM1");
		MatrixScreenPrintf(0, 425, inverseM2, "inverseM2");
		MatrixScreenPrintf(400, 25, transposeM1, "transposeM1");
		MatrixScreenPrintf(400, 125, transposeM2, "transposeM2");
		MatrixScreenPrintf(400, 225, identity, "identity");
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
