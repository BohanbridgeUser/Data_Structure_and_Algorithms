#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char argv[])
{
	int N;
	scanf("%d", &N);
	char gc;
	while ((gc = getchar()) != '\n');
	int* Set = (int*)malloc(N * sizeof(int));
	for (int i = 0; i < N; i++) Set[i] = -1;


	char a;
	int b, c;
	while (1) {
		char gc;
		scanf("%c", &a);
		if (a == 'C') {
			scanf("%d %d", &b, &c);
			b--, c--;
			int x = b, y = c;
			while (Set[x] >= 0) x = Set[x];
			while (Set[y] >= 0) y = Set[y];
			if (x != b) Set[b] = x;
			if (y != c) Set[c] = y;
			if (x == y) printf("yes\n");
			else printf("no\n");
			while ((gc = getchar()) != '\n');
		}
		else if (a == 'I') {
			scanf("%d %d", &b, &c);
			b--, c--;
			int x = b, y = c;
			while (Set[x] >= 0) x = Set[x];
			while (Set[y] >= 0) y = Set[y];
			if (Set[x] < Set[y]) Set[x] += Set[y], Set[y] = x,Set[c] = x;
			else if (Set[x] > Set[y]) Set[y] += Set[x], Set[x] = y,Set[b] = y;
			else if (Set[x] == Set[y])  Set[x] += Set[y], Set[y] = x, Set[c] = x;
			while ((gc = getchar()) != '\n');
		}
		else if (a == 'S') {
			int cnt = 0;
			for (int i = 0; i < N; i++) {
				if (Set[i] < 0) cnt++;
			}
			if (cnt > 1) {
				printf("There are %d components.\n", cnt);
			}
			else if (cnt == 1) {
				printf("The network is connected.\n");
			}
			break;
		}
	}
	return 0;
}