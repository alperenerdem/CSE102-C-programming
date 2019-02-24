/*161044027 Alperen ERDEM */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct rubick_s {
	int **face0;
	int **face1;
	int **face2;
	int **face3;
	int **face4;
	int **face5;
} Rubick;


int cubecreater(FILE *fp,Rubick *cube); /*rubik küp için hafızadan yer alıyorum */
int commandtaker(FILE *fp,Rubick *cube,int size);/*commands.txt'den komutları okuyor */
int shrinker(Rubick *cube,int size);/*n*n kübü n-1*n-1'e küçültüyor */
void rightleftrotater(FILE *fp,Rubick *cube,int face,int size);/*alınan komuta göre sağa sola çeviriyor */
void updownrotater(FILE *fp,Rubick *cube,int face,int size);/*alınan komuta göre aşağı yukarı çeviriyor */
int cubeprinter(int size,Rubick *cube);/*kübü dosyaya yazdırıyor */
void memoryfree(int size,Rubick *cube);/*hafızayı boşaltıyor */

int main(){
	FILE *fp;
	Rubick cube;
	int size,lastsize;/*size ilk size'mız lastsize ise shrinkten sonraki size */
	
	fp = fopen("commands.txt", "r");/*komutları almak için dosyayı açıyorum */
	size=cubecreater(fp,&cube);/*kübü oluşturmak için fonksiyona gönderiyorum */

	lastsize=commandtaker(fp,&cube,size); /*burdaki return değeri en son kübün size değeri */
	fclose(fp);

	cubeprinter(lastsize,&cube);/*kübü dosyaya yazıyorum */
	memoryfree(lastsize,&cube);/*hafızayı boşaltıyorum */
	
	return 0;
}

int cubecreater(FILE *fp,Rubick *cube){
	int a,b,c;/*a,size'ı aldığım değer return edicem, b c for için a' ile karşılaştıracağım for sayaçları */
	
	fscanf(fp,"%d",&a);

	cube->face0=malloc(sizeof(int*)*(a));/*arrayin ilk boyutu için hafızada yer alıyorum size kadar */
	for(b=0;b<a;b++){
		cube->face0[b]=malloc(sizeof(int)*(a));/*arrayın diğer boyutu için a kadar yer alıyorum tekrar( a size) */
		for(c=0;c<a;c++){
			cube->face0[b][c]=0;
		}
	}
	/*her face için 6 defa yapıyorum bunu */
	cube->face1=malloc(sizeof(int*)*(a));
	for(b=0;b<a;b++){
		cube->face1[b]=malloc(sizeof(int)*(a));
		for(c=0;c<a;c++){
			cube->face1[b][c]=1;
			
		}
	}
	cube->face2=malloc(sizeof(int*)*(a));
	for(b=0;b<a;b++){
		cube->face2[b]=malloc(sizeof(int)*(a));
		for(c=0;c<a;c++){
			cube->face2[b][c]=2;
		}
	}
	cube->face3=malloc(sizeof(int*)*(a));
	for(b=0;b<a;b++){
		cube->face3[b]=malloc(sizeof(int)*(a));
		for(c=0;c<a;c++){
			cube->face3[b][c]=3;
		}
	}
	cube->face4=malloc(sizeof(int*)*(a));
	for(b=0;b<a;b++){
		cube->face4[b]=malloc(sizeof(int)*(a));
		for(c=0;c<a;c++){
			cube->face4[b][c]=4;
		}
	}
	cube->face5=malloc(sizeof(int*)*(a));
	for(b=0;b<a;b++){
		cube->face5[b]=malloc(sizeof(int)*(a));
		for(c=0;c<a;c++){
			cube->face5[b][c]=5;
		}
	}
	
	return a;/*size'ı döndürüyorum */
}

void memoryfree(int size,Rubick *cube){/*hafızayı sırayla freeliyorum */
	int b;

	for(b=0;b<size;b++){
		free(cube->face0[b]);
	}
	free(cube->face0);
	
	for(b=0;b<size;b++){
		free(cube->face1[b]);
	}
	free(cube->face1);
	
	for(b=0;b<size;b++){
		free(cube->face2[b]);
	}
	free(cube->face2);
	
	for(b=0;b<size;b++){
		free(cube->face3[b]);
	}
	free(cube->face3);
		
	for(b=0;b<size;b++){
		free(cube->face4[b]);
	}
	free(cube->face4);
	
	for(b=0;b<size;b++){
		free(cube->face5[b]);
	}
	free(cube->face5);
	
}	
int commandtaker(FILE *fp,Rubick *cube,int size){
	char temp[20],temp2[20];
	int face,lastsize;
	lastsize=size;/*shrink için size'yı yeni değişkende tutuyorum */
	while(1){
		fscanf(fp,"%s",temp);/*rotate veya shrink komutunu alıyorum */
		if( feof(fp) )
		{ 
		 break ;
		}
	    if(strcmp(temp,"rotate")==0){
			fscanf(fp,"%d %s",&face,temp2);/*yüz sayısını ve row-column değişkenini alıyorum */
			if(strcmp(temp2,"row")==0){
			   rightleftrotater(fp,cube,face,lastsize);	/*rowsa sağa sola dönceği için sağa sola döndürme fonksiyonuna yolluyorum */
			}
			else if(strcmp(temp2,"column")==0){/*columnsa aşağı yukarı döndürme fonksiyonuna yolluyorum */	
			   updownrotater(fp,cube,face,lastsize);   
			}
	    }
	    else if(strcmp(temp,"shrink")==0){
				lastsize=lastsize-1;/*size'ı bir azaltıyorum */
				shrinker(cube,lastsize);/*shrinke yeni size ile yolluyorum */		
		}
	}
return lastsize;/*sonsize'ı returnluyorum */
}


int shrinker(Rubick *cube,int size){
	int b,c;/*b-c array sayaçları */
	/*size zaten shrink fonksiyonuna girmeden -1 gelmişti , 0.0'da artık 1.1deki değer olacağı için ,
	her b,c değerinde b+1 c+1 bulunacak bu yüzden her yüz için taşıyorum bunu*/
	for(b=0;b<size;b++){
		for(c=0;c<size;c++){
			cube->face0[b][c]=cube->face0[b+1][c+1];	
		}	
	}
	free(cube->face0[b]);/*son columnu freeliyorum */
	
	/*her yüz için aynı şeyleri tekrar yapıyorum */
	for(b=0;b<size;b++){
		for(c=0;c<size;c++){
			cube->face1[b][c]=cube->face1[b+1][c+1];
			
		}
	}
	free(cube->face1[b]);
	for(b=0;b<size;b++){
		for(c=0;c<size;c++){
			cube->face2[b][c]=cube->face2[b+1][c+1];
		}
	}
	free(cube->face2[b]);
	for(b=0;b<size;b++){
		for(c=0;c<size;c++){
			cube->face3[b][c]=cube->face3[b+1][c+1];
		}
	}
	free(cube->face3[b]);
	for(b=0;b<size;b++){
		for(c=0;c<size;c++){
			cube->face4[b][c]=cube->face4[b+1][c+1];
		}
	}
	free(cube->face4[b]);
	for(b=0;b<size;b++){
		for(c=0;c<size;c++){
			cube->face5[b][c]=cube->face5[b+1][c+1];
		}
	}
	free(cube->face5[b]);
}


void rightleftrotater(FILE *fp,Rubick *cube,int face,int size){
char temp[20];/*left/right için */
int tempnum,number;/*tempnum adres değişikliği için,number ise kaçıncı row */
int y;/*y ise döngüdeki column sayacı */
		fscanf(fp,"%d %s",&number,temp);
		/* burdaki değerleri bir kağıda küp çizerek koordinat yazarak buldum. bazı yüzlerde 
		mesela 0,1,2,3ü sağa sola çevirmek aynıyken,4 ü sağa çevirmek 5i tersten(0dan deilde size-0dan) sola çevirmekle aynı
		bu yüzden 4 ve 5 için ayrı kod yazdım.
		*/	
		if(face==4){
			 if(strcmp(temp,"right")==0){
			  	for(y=0;y<size;y++){/*size kadar adres değişikliği yapılacağı için döngü */
				  	tempnum=cube->face4[number][y];
				  	cube->face4[number][y]=cube->face3[(size-1)-y][number];
				  	cube->face3[(size-1)-y][number]=cube->face5[(size-1)-number][(size-1)-y];
				  	cube->face5[(size-1)-number][(size-1)-y]=cube->face1[y][(size-1)-number];
				  	cube->face1[y][(size-1)-number]=tempnum;
			 	}
			 }
			 else if(strcmp(temp,"left")==0){
			 	for(y=0;y<size;y++){
				  	tempnum=cube->face4[number][y];
				  	cube->face4[number][y]=cube->face1[y][(size-1)-number];
				  	cube->face1[y][(size-1)-number]=cube->face5[(size-1)-number][(size-1)-y];
				  	cube->face5[(size-1)-number][(size-1)-y]=cube->face3[(size-1)-y][number];
				  	cube->face3[(size-1)-y][number]=tempnum;	
				 } 	
			 }
		}	 
		else if(face==5){
			 if(strcmp(temp,"right")==0){
			  	for(y=0;y<size;y++){
				  	tempnum=cube->face5[number][y];
				  	cube->face5[number][y]=cube->face3[y][(size-1)-number]; 
				  	cube->face3[y][(size-1)-number]=cube->face4[(size-1)-number][(size-1)-y];
				  	cube->face4[(size-1)-number][(size-1)-y]=cube->face1[(size-1)-y][number];
				  	cube->face1[(size-1)-y][number]=tempnum;
			 	}
			 }
			 else if(strcmp(temp,"left")==0){
			 	for(y=0;y<size;y++){
				  	tempnum=cube->face5[number][y];
				  	cube->face5[number][y]=cube->face1[(size-1)-y][number]; 
				  	cube->face1[(size-1)-y][number]=cube->face4[(size-1)-number][(size-1)-y];
				  	cube->face4[(size-1)-number][(size-1)-y]=cube->face3[y][(size-1)-number];
				  	cube->face3[y][(size-1)-number]=tempnum;	
				 } 	
			 }	 
		}
		else if(face==0||face==1||face==2||face==3){
			 if(strcmp(temp,"right")==0){
	
				 for(y=0;y<size;y++){	
					 
				 	tempnum=cube->face0[number][y];
				 	cube->face0[number][y]=cube->face3[number][y];
				  	cube->face3[number][y]=cube->face2[number][y];
				  	cube->face2[number][y]=cube->face1[number][y];
				  	cube->face1[number][y]=tempnum;
				 } 	
			 }
			 else if(strcmp(temp,"left")==0){
			   	for(y=0;y<size;y++){	
			 		tempnum=cube->face0[number][y];
				 	cube->face0[number][y]=cube->face1[number][y];
				  	cube->face1[number][y]=cube->face2[number][y];
				  	cube->face2[number][y]=cube->face3[number][y];
				  	cube->face3[number][y]=tempnum;
				}	
			 }		
		}

}

void updownrotater(FILE *fp,Rubick *cube,int face,int size){
char temp[20];/*up/down */
int y;
int number,tempnum;
		fscanf(fp,"%d %s",&number,temp);
		/* bunuda aynı şekilde yaptım
		mesela 0-4-5i yukarı aşağı çevirmek aynıyken,2ye tersten geliyor bu değerler.
		aynı şekilde yüz 1 ve 3'te birbirlerine göre tersten.
		bu yüzden 1,2 ve 3 için ayrı kod yazdım.
		aslında bazı yüzlerin sağa çevrilmesi bazı yüzlerin aşağı çevrilmesiyle aynı fakat anlaşılmaz olabileceği için teker teker ayırdım.
		*/			
		
		if(face==1){
			 if(strcmp(temp,"up")==0){
			 	for(y=0;y<size;y++){	
			 		tempnum=cube->face1[y][number];
				 	cube->face1[y][number]=cube->face5[number][(size-1)-y];
				  	cube->face5[number][(size-1)-y]=cube->face3[(size-1)-y][(size-1)-number];
				  	cube->face3[(size-1)-y][(size-1)-number]=cube->face4[(size-1)-number][y];
				  	cube->face4[(size-1)-number][y]=tempnum;
				}	
			 }
			 else if(strcmp(temp,"down")==0){
			 	for(y=0;y<size;y++){	
			 		tempnum=cube->face1[y][number];
				 	cube->face1[y][number]=cube->face4[(size-1)-number][y];
				  	cube->face4[(size-1)-number][y]=cube->face3[(size-1)-y][(size-1)-number];
				  	cube->face3[(size-1)-y][(size-1)-number]=cube->face5[number][(size-1)-y];
				  	cube->face5[number][(size-1)-y]=tempnum;
				}
			 }
		}	 
		 else if(face==2){
			 if(strcmp(temp,"up")==0){
			 	for(y=0;y<size;y++){	
			 		tempnum=cube->face2[y][number];
				 	cube->face2[y][number]=cube->face5[(size-1)-y][(size-1)-number];
				  	cube->face5[(size-1)-y][(size-1)-number]=cube->face0[(size-1)-y][(size-1)-number];
				  	cube->face0[(size-1)-y][(size-1)-number]=cube->face4[(size-1)-y][(size-1)-number];
				  	cube->face4[(size-1)-y][(size-1)-number]=tempnum;
				}	
			 }
			 else if(strcmp(temp,"down")==0){
			 	for(y=0;y<size;y++){	
			 		tempnum=cube->face2[y][number];
				 	cube->face2[y][number]=cube->face4[(size-1)-y][(size-1)-number];
				  	cube->face4[(size-1)-y][(size-1)-number]=cube->face0[(size-1)-y][(size-1)-number];
				  	cube->face0[(size-1)-y][(size-1)-number]=cube->face5[(size-1)-y][(size-1)-number];
				  	cube->face5[(size-1)-y][(size-1)-number]=tempnum;
				}
			 }	 
		}
		 else if(face==3){
			 if(strcmp(temp,"up")==0){
			 	for(y=0;y<size;y++){	
			 		tempnum=cube->face3[y][number];
				 	cube->face3[y][number]=cube->face5[(size-1)-number][y];
				  	cube->face5[(size-1)-number][y]=cube->face1[(size-1)-y][(size-1)-number];
				  	cube->face1[(size-1)-y][(size-1)-number]=cube->face4[number][(size-1)-y];
				  	cube->face4[number][(size-1)-y]=tempnum;
				}	
			 }
			 else if(strcmp(temp,"down")==0){
			 	for(y=0;y<size;y++){	
			 		tempnum=cube->face3[y][number];
				 	cube->face3[y][number]=cube->face4[number][(size-1)-y];
				  	cube->face4[number][(size-1)-y]=cube->face1[(size-1)-y][(size-1)-number];
				  	cube->face1[(size-1)-y][(size-1)-number]=cube->face5[(size-1)-number][y];
				  	cube->face5[(size-1)-number][y]=tempnum;
				}
			 }	 
		}
		else if(face==0||face==4||face==5){
			 if(strcmp(temp,"up")==0){
			 	for(y=0;y<size;y++){	
			 		tempnum=cube->face0[y][number];
				 	cube->face0[y][number]=cube->face5[y][number];
				  	cube->face5[y][number]=cube->face2[(size-1)-y][(size-1)-number];
				  	cube->face2[(size-1)-y][(size-1)-number]=cube->face4[y][number];
				  	cube->face4[y][number]=tempnum;
				}
			 }
			 else if(strcmp(temp,"down")==0){
			 	for(y=0;y<size;y++){	
			 		tempnum=cube->face0[y][number];
				 	cube->face0[y][number]=cube->face4[y][number];
				  	cube->face4[y][number]=cube->face2[(size-1)-y][(size-1)-number];
				  	cube->face2[(size-1)-y][(size-1)-number]=cube->face5[y][number];
				  	cube->face5[y][number]=tempnum;
				}
			 }		
		}
}
		

int cubeprinter(int size,Rubick *cube){
	FILE* fp;
	int a,b=0,c=0;
	a=size;
	fp = fopen ("results.txt", "w+");/*dosyaya yazdırmak için results.txt'e açıyorum*/
	/*gönderilen size kadar elemanı dosyaya sırayla yazdırıyor. Her eleman arasında boşluk,
	 sutün aralarında yeni satır ve yüz aralarında bir boşluklu satır bırakıyor.
	*/
	for(b=0;b<a;b++){
		
		for(c=0;c<a;c++){
			fprintf(fp,"%d ",cube->face0[b][c]);
		}
		fprintf(fp,"\n");
	}
	fprintf(fp,"\n");
	for(b=0;b<a;b++){
		
		for(c=0;c<a;c++){
			fprintf(fp,"%d ",cube->face1[b][c]);
		}
		fprintf(fp,"\n");
	}
	fprintf(fp,"\n");
	for(b=0;b<a;b++){
		
		for(c=0;c<a;c++){
			fprintf(fp,"%d ",cube->face2[b][c]);
		}
		fprintf(fp,"\n");
	}
	fprintf(fp,"\n");
	for(b=0;b<a;b++){
		
		for(c=0;c<a;c++){
			fprintf(fp,"%d ",cube->face3[b][c]);
		}
		fprintf(fp,"\n");
	}
	fprintf(fp,"\n");
	for(b=0;b<a;b++){
		
		for(c=0;c<a;c++){
			fprintf(fp,"%d ",cube->face4[b][c]);
		}
		fprintf(fp,"\n");
	}
	fprintf(fp,"\n");
	for(b=0;b<a;b++){
		
		for(c=0;c<a;c++){
			fprintf(fp,"%d ",cube->face5[b][c]);
		}
		fprintf(fp,"\n");
	}
	fclose(fp);
}
