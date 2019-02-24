/* 161044027 Alperen Erdem */
#include<stdio.h>


int main()
{
	float x,y,z=0,boardHeight=200,boardWeight=300,detectorHeight=20,detectorWeight=20,regionHeight=20,regionWeight=20,regionX=100,regionY=100,tempx,tempy;
	/* height ve weight'leri merkezden köşeye olan uzaklık olarak kullandım. Weight=x ekseninde merkezden köşeye, Height=y ekseninden merkezden köşeye uzaklık,
	  regionX-Y'ler gemimizin olduğu yerin koordinatlarını veriyor*/
	int attempts=10;
		
			if(detectorHeight*detectorWeight>=regionHeight*regionWeight){ /* Oyunun işaretli alan ve detektör için bug kontrolu */
				printf("Board = [%.2f,%.2f],Detector = [%.2f,%.2f],Region = [%.2f,%.2f]\n", boardHeight,boardWeight,detectorHeight,detectorWeight,regionHeight,regionWeight);
				while(z==0){/* z oyun bitene kadar 0 kalıcak döngümüz için*/
					printf("Enter the x coordinate of the move:\n");
					scanf("%f",&x);
					printf("Enter the y coordinate of the move:\n");
					scanf("%f",&y);
						 if(x==regionX&&y==regionY){ /* eğer direk işaretli alanın merkezini yazarsa oyunu kazanmış oluyor döngüden çıkıyoruz*/
					 		
					 		break;
					 			}
					 if((x>regionX+regionWeight||x<regionX-regionWeight)||(y>regionY+regionHeight||y<regionY-regionHeight)){ /* işaretli alanda değilse kullanıcıya bildirip hakkından bir düşüyor */
						attempts=attempts-1;
						printf("You missed the target, attempts remaining: %d\n",attempts);
								if(attempts==0){ /* hakkı bittiyse kaybediyor*/
									printf("You Lost Bro, Try again\n");
									return 0;
								}
			
					}
					 if((x<=regionX+regionWeight&&x>=regionX-regionWeight)&&(y<=regionY+regionHeight&&y>=regionY-regionHeight)){/* işaretli alan içindiyse if'e giriyor */
					 		
					 		attempts=attempts-1; 
					 		detectorHeight=detectorHeight/2;
					 		detectorWeight=detectorWeight/2;
					 		tempx=regionX;
					 		tempy=regionY;
					 		/* hakkından bir düşüp dedektör yarıçapını azaltıyor bölgenin x ve y'sini tempe atıyor. Çünkü sonradan bölgenin merkezden köşeye olan uzaklığını bulmak için kullanacağız*/
					 		if(x>regionX) /* bölgenin merkezin sağında mı solundamı olduğuna bakıyor */
					 			{
					 			regionX=regionX-detectorWeight*2+(x-regionX)*1/2; /*kalan bölgenin merkezini bulup yarıçapını tekrar hesaplıyor*/
					 			regionWeight=regionX-(tempx-detectorWeight*2);
					 			
					 			}
					 		else if(x<regionX)
					 			{regionX=regionX+detectorWeight*2+(x-regionX)*1/2;	
					 			regionWeight=tempx+detectorWeight*2-regionX;
					 			}
					 		if(y>regionY)/* bölgenin merkezin yukarısında mı aşağısındamı olduğuna bakıyor */
					 			{regionY=regionY-detectorHeight*2+(y-regionY)*1/2;
					 			regionHeight=regionY-(tempy-detectorHeight*2);
					 			
					 			}
					 		else if(y<regionY)
					 			{regionY=regionY+detectorHeight*2+(y-regionY)*1/2;
					 			regionHeight=tempy+detectorHeight*2-regionY;
					 			
					 			}
					 	
					 		printf("Partial hit! marked region was shirked to [%.2f x %.2f], detector was shirked to [%.2f x %.2f] attempts remaining: %d\n" ,
					 		 regionHeight,regionWeight,detectorHeight,detectorWeight,attempts);
					 		printf("Board = [%.2f,%.2f],Detector = [%.2f,%.2f],Region = [%.2f,%.2f]\n %.2f %.2f \n",
					 		 boardWeight,boardHeight,detectorWeight,detectorHeight,regionWeight,regionHeight,regionX,regionY);
					}
				
						 	if(regionHeight<=0||regionWeight<=0)
							{	
								 z=1; /* eğer bölge kalmadıysa döngüden çıkıyor*/
								 break;
							}
					else if(x>boardWeight || y>boardHeight){ /* seçilen yer oyun alanında değilse hata veriyor*/
						printf("Error, move is not valid. Try again. Attempts remaining: %d\n",attempts);
			
					}
					if(attempts==0){/* hakkı kalmadıysa oyun bitiyor*/
									printf("You Lost Bro, Try again\n");
									return 0;
					}	
				}

				if(attempts!=0){/* hakkı var ve işaretli bölge kalmadıysa oyunu kazanıyor*/
						printf("You did it mate, Enjoy your <<VictorY>>\n");
						return 0;
				}		
			}
			else{/*dedektör işaretli alandan küçükse oyunu başlamadan kapatıyor.*/
				printf("Detector must be bigger than the marked area\n");
				return 0;
			}
		
		
}
