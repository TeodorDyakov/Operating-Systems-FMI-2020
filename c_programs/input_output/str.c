#include<string.h>
#include<stdio.h>

int main(){
		

	int n = 10;
	char a[n];
	a[n-1] = '\0';
	
	for(int i = 0; i < n; i++){
		printf("%d\n", a[i]);
	}

	printf("%ld\n", strlen(a));
	
	strncpy(a, "12", 9);

	printf("%s\n", a);
	
}
