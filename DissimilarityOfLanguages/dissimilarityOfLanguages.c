/*161044027 Alperen ERDEM */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXSIZE 728 /*27 kullanabilir karakter olduğu ve bigramlar 2li olduğu için en fazla 27*27+1
					(son elemanı nullamak için +1, çift boşluk için değil) lik array kullanacağız
					 böylece en büyük inputta bile çalışacak kodumuz. */

int bigramtaker(char* filename,char bigrams[MAXSIZE][3],int bigramcount[MAXSIZE],double bigramfrequencies[MAXSIZE]);
int dissimilarity(char* filename1,int bigramsize2,char bigrams2[MAXSIZE][3],double bigramfrequencies2[MAXSIZE]);

int main(){/* 'language.x'in değerlerini dosyayı fazladan boşuna okumamak için mainde alıyorum.*/
	int bigramcount2[MAXSIZE],bigramsize2;/*bigramcount language'xin bigramlarının tekrar sayılarını,bigramsize farklı 
										  bigram miktarını*/
	char bigrams2[MAXSIZE][3];			  /*bigrams farklı bigramları */
	double bigramfrequencies2[MAXSIZE];	  /*bigramfrequencies te frekansları tutuyor*/		
	bigramsize2=bigramtaker("language_x.txt",bigrams2,bigramcount2,bigramfrequencies2);/*languagexin frekans ve bigramlarını 
																						almak için fonksiyona yolluyorum */
	dissimilarity("language_1.txt",bigramsize2,bigrams2,bigramfrequencies2);/*language x değerleriyle language_1.txtini diss 
																			fonksiyonua yolluyorum. */
	dissimilarity("language_2.txt",bigramsize2,bigrams2,bigramfrequencies2);
	dissimilarity("language_3.txt",bigramsize2,bigrams2,bigramfrequencies2);
	dissimilarity("language_4.txt",bigramsize2,bigrams2,bigramfrequencies2);
	dissimilarity("language_5.txt",bigramsize2,bigrams2,bigramfrequencies2);

	return 0;
}
/* ilk önce bigramtaker fonksiyonunu kontrol ederseniz anlaşılması daha kolay olur. 73.satırda.*/


int dissimilarity(char* filename1,int bigramsize2,char bigrams2[MAXSIZE][3],double bigramfrequencies2[MAXSIZE])
{
int bigramcount1[MAXSIZE],bigramsize1,a,b;/*countu burda kullanmıyorum fakat bigramteker fonksiyonuna yollamak için tanımladım */
										  /*1 sonlu değişkenler ilk gelen txt için değer tutucuları ,a,b döngü değişkenleri*/
char bigrams1[MAXSIZE][3];
double bigramfrequencies1[MAXSIZE],diss=0;
bigramsize1=bigramtaker(filename1,bigrams1,bigramcount1,bigramfrequencies1);/*size'ı bigramtakerden alıyorum */
	/*ilk önce algoritmamı açıklayayım. Tersten gidiyorum genel olarak
	ilk önce tüm frekans değerlerini 2 input dosyası için topluyorum. aynı bigramlar için fazladan toplanmış oluyor
	sonra aynı bulunan bigramlar için mesela 'ad' ikisindede var, iki inputtaki frekansınıda çıkarıyorum ve farkını topluyorum. 
	ilk iki while tüm frekansları topluyor*/
	
	a=0;
	while(a<bigramsize2){
	diss=diss+bigramfrequencies2[a];
	a++;
	}
	a=0;
	while(a<bigramsize1){
	diss=diss+bigramfrequencies1[a];
	a++;
	}
	
	/*forda ise aynı bigramları tespit edip ilk önce 2 inputtaki frekansınıda çıkarıp farkını topluyorum */
	for(a=0;a<bigramsize2;a++){
		
		for(b=0;b<bigramsize1;b++){
			if(strcmp(bigrams2[a],bigrams1[b])==0){
				diss=diss-(bigramfrequencies2[a]+bigramfrequencies1[b]);
				if(bigramfrequencies2[a]-bigramfrequencies1[b]>=0){
					diss=diss+(bigramfrequencies2[a]-bigramfrequencies1[b]);
				}	
				else if(bigramfrequencies2[a]-bigramfrequencies1[b]<0){
					diss=diss-(bigramfrequencies2[a]-bigramfrequencies1[b]);
				}
				break;/*aynıyı bulduktan sonra boşuna çalışmaması için break*/ 
			}
		}

	}	
	printf("dissimilarity(language_x, %s)== %f\n",filename1,diss);/* sonra ekrana sonucuyazdırıyorum.*/
	return 1;
}

int bigramtaker(char* filename,char bigrams[MAXSIZE][3],int bigramcount[MAXSIZE],double bigramfrequencies[MAXSIZE]){
	FILE *fp;
	fp = fopen(filename, "r");/*dosyayı açıyorum */
	char tempword[50]; /*geçici kelime tutacağım */
	char tempbigram[3]; /* geçiçi hece tutacağım size 3 vermemim sebebi son elemanı nullamak için.*/
	int a,b=0,c,bigramsize=0,lenghtword,flag=0;/*a,b,c for/while döngüsü sayaçları,bigramsize farklı bigrammiktarını tutuyor
												 lenghtword kelimenin uzunluğu(her kelimede uzunluk +1 kadar bigram bulunuyor
												 flag ise bigramın daha önce olup olmadığını kontrol etmek için*/
	while(1){
		if( feof(fp) )/* dosyanın sonunda döngüden çıksın*/
         { 
         break ;
         }
		fscanf(fp,"%s ",tempword);/*kelimeyi alıyorum*/
		lenghtword=strlen(tempword);/*uzunluğunu ölçüyorum */
	
		tempword[lenghtword]='\0';/*kelimenin son elemanını nulluyorum ki junk değer kalmasın */
		a=0;
		
		while(lenghtword+1>a){/*kelimenin uzunluğu+1 kadar bigram bulunuyor */
			if(a!=0&&a!=lenghtword){/*ilk ve son harf ise farklı birşey yapacağım, değilse*/
				tempbigram[0]=tempword[a-1];/*tempbigramın ilkine a-1in elemanı atıyorum.(a=0 ise buraya giremez) */
				
				tempbigram[1]=tempword[a];/*tembigramın 2.elemanına da a.ın elemanı atıyorum. */
				tempbigram[2]='\0';/*son elemanıda nulluyorum ki junk kalmasın */

			}	
			else if(a==lenghtword){/*son eleman ise */
				
				tempbigram[0]=tempword[a-1]; /*sonuncu charı atıyorum*/
				tempbigram[1]=' ';/*son elemanıda boşluk atıyorum */
				tempbigram[2]='\0';/*son elemanıda nulluyorum ki junk kalmasın */
			}	
			else if(a==0){/*ilk eleman ise*/
				tempbigram[0]=' ';/* ilk önce boşluk atıyorum*/
				tempbigram[1]=tempword[a];/*sonra ilk charı atıyorum tempworda */
				tempbigram[2]='\0';/*son elemanıda nulluyorum ki junk kalmasın */
			}
				
			b=b+1;/* total bigramsayacı*/
			a=a+1;/* kelime içindeki harf sayacı*/
			c=0;/* bigram kıyaslama sayacı*/
			flag=0;/*bigram daha önce varsa flag 1lenecek */
			while(bigramsize!=0&&c<bigramsize+1){/*daha önceki (anlık bigramsize kadar) bigramlarla kıyaslama */
					if(strcmp(tempbigram,bigrams[c])==0){
					flag=1;
					bigramcount[c]=bigramcount[c]+1;/*daha önce varsa ordaki countu 1 arttırıyorum */
					break;
					}			
				c++;
			}
			/*dahaönce bigram bulunmadıysa */
			if(flag!=1){
				strcpy(bigrams[bigramsize],tempbigram);/*bigrams arrayine bigramı atayıp değerleri arttırıyorum */
				bigrams[bigramsize+1][0]='\0';/*sonraki elemanı nulluyorum junk değer için */
				bigramcount[bigramsize]=1;
				bigramcount[bigramsize+1]='\0';/*junk değerler için sonraki elemanı nulluyorum */
				bigramsize=bigramsize+1;
			}	
		}	
	}
	for(a=0;a<bigramsize+1;a++){/* frekans buluyorum burda tüm değerler hesaplandıktan sonra*/
	    bigramfrequencies[a]=(float)bigramcount[a]/(float)(b);
	}
	 bigramfrequencies[a+1]='\0';

	fclose(fp);/*dosyayı kapatıp bigramsize+1i returnluyorum */ 
	return bigramsize+1;
}

