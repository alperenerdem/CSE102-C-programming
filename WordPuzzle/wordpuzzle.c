/*161044027 Alperen ERDEM */
#include<stdio.h>
#include <string.h>

#define MAXROWSLENGHT 250
#define MAXROWS 100
int main(){

	readfileandsearch("input.txt","Xanthos");
	readfileandsearch("input.txt","Patara");
	readfileandsearch("input.txt","Myra");
	readfileandsearch("input.txt","Arycanda");
	readfileandsearch("input.txt","Phaselis");
	return 0;
}


int readfileandsearch(char* filename,char* word){
	FILE *fp;
	char wordboard[MAXROWS][MAXROWSLENGHT];
	int x=0,y;
	fp = fopen(filename, "r");
    while(1){  
         if( feof(fp) )/* dosyanın sonunda döngüden çıksın*/
         { 
         break ;
         }
		 
		 fscanf(fp,"%s ",wordboard[x]); /*stringleri row row(satır satır) alıyorum*/
		 x=x+1;
	}
 	searchword(word,wordboard,x);/*aldığım satırlardan oluşturduğum gameboardı aradığım kelimeyi ve satır sayısını kelime bulma fonksiyonuna yolluyorum. */
	return 0;
}

int searchword(char *searchword,char board[MAXROWS][MAXROWSLENGHT],int rowcount){
	int x=0,y=0,a=0,b,c=0,tempx,tempy; /* a word counterimiz, x row kıyaslayıcı, y rowdaki sayacımız bir nevi column. c aradığımız kelimeyi teker teker b kadar atamak için sayacımız. 
										  tempx ve tempyx bulunan kelimeyi kıyaslerken girilen döngüde, kaldığımız yeri kaybetmememiz için değişken*/
	b=strlen(searchword); /*b aradığımız kelimenin uzunluğu */
	char findword[b]; /*boardda bulduğumuz kelimeyi atacağımız string */
	
	while(x<rowcount){/* kaç adet row olduğu kadar bakacağız*/
		while(board[x][y]!='\0'){ /* rowda null eleman görünce alt rowa geçicez*/
			if(searchword[a]==board[x][y]){/*ilk harf eşleşince kelime arama döngüsüne giriyorum */
				tempx=x;/*x yani vertical bakcağımız için xi tempe atıyorum*/
				
				while(b>c){
				findword[c]=board[x][y];/*vertical şekilde strlen(kelime) kadar ilk harfin eşleştiği yerden kelimeyi alıyorum*/
				x++;
				c++;		
				}	
				x=tempx;	/*xi kaldığımız yerden devam etmek için tempxten alıyorum */
				
				if(strcmp(searchword,findword)==0){/*kelimeyi kıyaslıyorum eğer kelime eşitse nerde bulduğunu yazıyor */
					printf("%s (%d,%d) Vertical \n",findword,x+1,y+1);
				}
			
				findword[0]='\0';/*junk elemanlardan kullanmak için ilk harfi nulluyorum*/
				findword[b]='\0';/*junk elemanlardan kullanmak için son harften sonraki harfi nulluyorum*/
				c=0;
				tempy=y;/*horizontal bakacağım için y'yi tempy'ye atıyorum */
				
				while(b>c){
				findword[c]=board[x][y];/*horizontal olarak kelimeyi alıyorum*/
				y++;
				c++;
				}	
				
				y=tempy;	
				if(strcmp(searchword,findword)==0){/*kelimeyi kıyaslıyorum doğru ise nerde olduğunu yazıyor */
					printf("%s (%d,%d) Horizontal \n",findword,x+1,y+1);
				}
			
				findword[0]='\0';/*junk elemanlardan kullanmak için ilk harfi nulluyorum*/
				findword[b]='\0';/*junk elemanlardan kullanmak için son harften sonraki harfi nulluyorum*/
				c=0;		
				}
			y++;
		}
		x++;
		y=0;/*diğer rowda sıfırdan başlaması için column tutan y'yi sıfırlıyorum */
	}
	return 0;
}

