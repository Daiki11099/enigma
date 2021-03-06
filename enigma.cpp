#include <stdio.h>

void SwapArray(int rotor[][2]);

int main(int argc, char *argv[])
{
	char alpha[26]  = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
	int rotor1[26][2] = {{12, 14}, {6, 2}, {22, 4}, {3, 6}, {11, 20}, {10, 9}, {25, 19},
	                     {15, 10}, {4, 3}, {18, 25}, {19, 15}, {26, 1}, {8, 21}, 
						 {13, 13}, {5, 8}, {17, 11}, {24, 23}, {7, 22}, {9, 5}, {16, 17},
						 {14, 18}, {20, 12}, {21, 24}, {2, 26}, {23, 7}, {1, 16}};
	int rotor2[26][2] = {{10, 3}, {18, 5}, {2, 4}, {3, 18}, {8, 12}, {16, 11}, {20, 7},
	                     {24, 23}, {11, 17}, {17, 16}, {1, 21}, {21, 2}, {4, 22}, {26, 6},
						 {13, 25}, {12, 1}, {14, 19}, {25, 24}, {5, 9}, {22, 26}, {9, 13},
						 {7, 14}, {19, 20}, {15, 8}, {23, 15}, {6, 10}};
	int rotor3[26][2] = {{5, 10}, {15, 8}, {21, 4}, {12, 17}, {18, 22}, {6, 9}, {24, 16},
	                     {2, 21}, {26, 1}, {3, 25}, {23, 12}, {14, 11}, {19, 3}, {17, 19},
						 {25, 23}, {11, 2}, {16, 18}, {20, 26}, {4, 15}, {10, 24}, {1, 13},
						 {22, 5}, {13, 7}, {7, 6}, {9, 20}, {8, 14}};
	const int ref[26] = {6, 21, 5, 24, 3, 1, 10, 20, 13, 7, 18, 14, 9, 12, 26, 23, 22, 11, 25,
	                     8, 2, 17, 16, 4, 19, 15};
	char code; //文字の入出力
	int Aflag = 0; //大文字か小文字の判定
	int ChangeRotor = 0; //何回転かを数える
	int i; //ステップ変数
	int num; //特定の配列の要素数を記憶するための変数
	FILE *from, *to;
	
	if (argc != 3) {
		printf("引数が違います。プログラムを終了します\n");
		return -1;
	}
	
	if ((from = fopen(argv[1], "r")) == NULL || (to = fopen(argv[2], "w")) == NULL) {
		printf("ファイルを正常に開けませんでした\n");
		return -1;
	}
	
	do {
		printf("ローター1を初期位置から26分の何回転させますか?(暗号化させる時と復号化させる時で揃えて下さい): ");
		scanf("%d", &ChangeRotor);
		while ((getchar()) != '\n');
	} while (ChangeRotor < 0);
	

	while ((code = fgetc(from)) != EOF) {
		if (code >= 'a' && code <= 'z') Aflag = 0;
		else if (code >= 'A' && code <= 'Z') Aflag = 1; 
		if ((code < 'a' || code > 'z') && (code < 'A' || code > 'Z')) {
			fputc(code, to);
			continue;
		}
		for (i = (ChangeRotor && 1); i > 0; i--) {
			SwapArray(rotor1);
			if (!(ChangeRotor % 26)) SwapArray(rotor2);
			if (!(ChangeRotor % 676)) SwapArray(rotor3);
		}

		//ここからローターの処理
		if (Aflag) {
			num = (code + 32) - 'a';
		}
		else {
			num = code - 'a';
		}
		//ローター1
		num = rotor1[num][0];
		for (i = 0; i < 26; i++) {
			if (rotor1[i][1] == num) {
				num = i;
				break;
			}
		}
		//ローター2
		num = rotor2[num][0];
		for (i = 0; i < 26; i++) {
			if (rotor2[i][1] == num) {
				num = i;
				break;
			}
		}
		//ローター3
		num = rotor3[num][0];
		for (i = 0; i < 26; i++) {
			if (rotor3[i][1] == num) {
				num = i;
				break;
			}
		}
		//リフレクタ
		num = ref[num] - 1;
		//ローター3再帰
		num = rotor3[num][1];
		for (i = 0; i < 26; i++) {
			if (rotor3[i][0] == num) {
				num = i;
				break;
			}
		}
		//ローター2再帰
		num = rotor2[num][1];
		for (i = 0; i < 26; i++) {
			if (rotor2[i][0] == num) {
				num = i;
				break;
			}
		}
		//ローター1再帰
		num = rotor1[num][1];
		for (i = 0; i < 26; i++) {
			if (rotor1[i][0] == num) {
				num = i;
				break;
			}
		}
		if (Aflag) {
			fputc(alpha[num] - 32, to);
		}
		else {
			fputc(alpha[num], to);
		}
		ChangeRotor++;
	}
}

void SwapArray(int rotor[][2])
{
	int swap;
	for (int i = 25; i > 0; i--) {
		for (int j = 0; j < 2; j++) {
			 swap = rotor[i][j];
			 rotor[i][j] = rotor[i - 1][j];
			 rotor[i - 1][j] = swap;
		}
	}
}