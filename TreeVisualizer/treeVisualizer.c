/*161044027 Alperen ERDEM */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LENGHT 101 /*input dosyanın max lenght'i */

void reader(char *filename,char getline[MAX_LENGHT]);    /*dosya okuyucu */
int parser(char line[MAX_LENGHT],int lenght,int cursor,int dallanma);
int treeprinter(int dallanma);/*başa '-' koymak için fonksiyon */

int main(){
	int cursor=0,dallanma=0,size; /*size stringin uzunluğunu tutuyor. cursor ve dallanma sayaçlar, ayrı bir fonksiyonda tanımlamıştım fakat kısaltmak için buraya koydum */
	char line[MAX_LENGHT];/*dosyadan alacağımız satır */
	reader("input.txt",line);
	size=strlen(line); /*uzunluğunu size'a atıyorum */
	parser(line,size,cursor,dallanma);/*sayaçlarla beraber bölücü fonksiyona atıyorum */
	/*printf("\n"); */
	/*pdfte ekstra newline basmayın yazdığı için burdaki 'printf("\n");'i yorum satırına aldım. terminalde kötü gözüktüğü için de belirtmek istedim */
	return 1; 
}

void reader(char *filename,char getline[MAX_LENGHT]){

	 FILE *fp;
	 fp = fopen(filename, "r");	 
	 fgets(getline,MAX_LENGHT,fp);/*dosyayı açıp,fgets ile stringe alıp kapatıyorum*/	 
	 fclose(fp);
}

int parser(char line[MAX_LENGHT],int lenght,int cursor,int dallanma){	
	if(lenght==1){/*lenght 1e indiğinde birşey yapmaması için stop değerim.lenghti azaltarak gideceğim*/
		return 1;
	}
	if(line[cursor]==','){/* ',' karakteri, treede farklı eleman olduğu için yeni satıra geçmemi söylüyor */
		printf("\n");
	}
	else if(line[cursor]=='('){/*'(' treedeki dal sayısının arttığını gösteriyor */
		dallanma=dallanma+1;
	}
	else if(line[cursor]==')'){/*')' treedeki dal sayısının azaldığını gösteriyor */
		dallanma=dallanma-1;
	}
	else if((line[cursor]>='a'&&line[cursor]<='z')||(line[cursor]>='A'&&line[cursor]<='Z')){/*karakter eğer harf ise dallanmasını ve kendisini ekrana basıyoruz */
		treeprinter(dallanma);/*dallanma sayacını '-' koyan fonksiyona gönderiyor */
		printf("%c",line[cursor]);
	}
	cursor++;/*sonraki chara geçmek için cursoru 1 arttırıyorum */
	lenght=lenght-1;/*lenghti 1 azaltıp fonksiyonu bir daha çağırıyoruz */
	parser(line,lenght,cursor,dallanma);
	return 1;
}

int treeprinter(int dallanma){
	printf("-");/*ilk dalı koyuyoruz çünkü dallanma 1 olsada dal olacak bir tane */
	dallanma=dallanma-1;/*dal sayacını azaltıyoruz,eğer 1den küçükse returnluyoruz. */
	if(dallanma<1){
		return 0;
	}
	treeprinter(dallanma);/*fonksiyonu tekrar çağrıyoruz. */
	return 1;
}
