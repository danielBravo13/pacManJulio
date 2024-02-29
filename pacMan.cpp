#include <stdio.h>
#include <allegro.h>
#include <time.h>

#define VELOCIDAD      100 //No usar valores negativos 
void init();
void motorJuego();
void cargarMapa1(int matrizJuego[20][30]);
void pintarMapa(int matrizJuego[20][30], BITMAP *buffer);
void movimientoPacMan(int matrizJuego[20][30], int posPacMan[2]);
void fantasmaNaranja(int matrizJuego[20][30], int orangeGhost[2]);
void fantasmaSalir(int matrizJuego[20][30], int orangeGhost[2], int gNum);


int main(){
	srand(time(NULL));
	init();
	motorJuego();
	return 0;
}
END_OF_MAIN();

void init(){

	int depth, res,cancion;
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0) 
		depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 900, 635, 0, 0);
	if (res != 0) {
		allegro_message(allegro_error);
		exit(-1);
	}
	set_window_title("Pac_Man Game");
	
	install_timer();
	install_keyboard();
	install_mouse();
	show_mouse(screen);
} 

void motorJuego(){
	BITMAP *buffer = create_bitmap(960,660);
    int op=2;
    int contRep=0;
    int matrizJuego[20][30];
    int pacManPos[2];
    int orangeGhostPos[2];
    orangeGhostPos[0]=10;
    orangeGhostPos[1]=15;
    pacManPos[0]=14;
    pacManPos[1]=14;
    cargarMapa1(matrizJuego);
    do{
    	pintarMapa(matrizJuego, buffer);
        movimientoPacMan(matrizJuego,pacManPos);
        blit(buffer, screen, 0,0,0,0,960,660);
        clear(buffer);
        rest(VELOCIDAD);
        contRep++;
        if(contRep==100){
        	fantasmaSalir(matrizJuego,orangeGhostPos,9);	
		}
		if(contRep>=120 && contRep%5==0){
			fantasmaNaranja(matrizJuego,orangeGhostPos);
		}
    }while(op==2);
}

void cargarMapa1(int matrizJuego[20][30]){
    //Guarda informacion del mapa
    int mapa[20][30] ={
       //0,1,2,3,4,5,6,7,8,9,1,1,2,3,4,5,6,7,8,9,2,1,2,3,4,5,6,7,8,9
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},//0
        {1,5,4,4,4,4,4,4,4,4,4,4,4,4,1,1,4,4,4,4,4,4,4,4,4,4,4,4,5,1},//1
        {1,4,1,4,1,1,4,1,1,1,1,4,1,4,1,1,4,1,4,1,1,1,1,4,1,1,4,1,4,1},//2
        {1,4,1,4,1,1,4,1,1,4,4,4,1,4,4,4,4,1,4,4,4,1,1,4,1,1,4,1,4,1},//3
        {1,4,1,4,1,1,4,4,4,4,1,4,1,4,1,1,4,1,4,1,4,4,4,4,1,1,4,1,4,1},//4
        {1,4,4,4,4,4,4,1,4,1,1,4,1,4,4,4,4,1,4,1,1,4,1,4,4,4,4,4,4,1},//5
        {1,4,1,1,4,1,1,1,4,4,1,4,1,4,1,1,4,1,4,1,4,4,1,1,1,4,1,1,4,1},//6
        {1,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,1},//7
        {1,4,1,1,1,4,1,4,1,1,1,1,4,1,1,1,1,4,1,1,1,1,4,1,4,1,1,1,4,1},//8
        {1,4,1,1,1,4,1,4,1,1,1,1,4,1,6,8,1,4,1,1,1,1,4,1,4,1,1,1,4,1},//9
        {4,4,4,4,4,4,1,4,4,1,1,1,4,1,7,9,1,4,1,1,1,4,4,1,4,1,1,1,4,4},//10
        {1,4,1,1,1,4,1,1,4,4,4,4,4,1,1,1,1,4,4,4,4,4,1,1,4,1,1,1,4,1},//11
        {1,4,1,4,4,4,4,4,4,1,1,1,4,4,4,4,4,4,1,1,1,4,4,4,4,4,4,1,4,1},//12
        {1,4,1,4,1,1,4,1,1,1,1,1,4,1,1,1,1,4,1,1,1,1,1,4,1,1,4,1,4,1},//13
        {1,4,1,4,1,4,4,4,1,4,4,4,4,4,0,4,4,4,4,4,4,1,4,4,4,1,4,1,4,1},//14
        {1,4,1,4,4,4,1,4,4,4,1,1,4,1,1,1,1,4,1,1,4,4,4,1,4,4,4,1,4,1},//15
        {1,4,1,4,1,4,4,4,1,4,1,1,4,4,4,4,4,4,1,1,4,1,4,4,4,1,4,1,4,1},//16
        {1,4,1,4,1,1,4,1,1,4,1,1,4,1,1,1,1,4,1,1,4,1,1,4,1,1,4,1,4,1},//17
        {1,5,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,1},//18
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} //19
    };
    for(int i=0;i<20;i++){
        for(int j=0;j<30;j++){
            matrizJuego[i][j]=mapa[i][j];
        }  
    }
}

void pintarMapa(int matrizJuego[20][30], BITMAP *buffer){
	BITMAP *vectorMapa[10];
	vectorMapa[0]= load_bitmap("CuerpoPacman_II.bmp", NULL);
	vectorMapa[1]= load_bitmap("Bloques_7.bmp", NULL);
	vectorMapa[2]= load_bitmap("PuntosChicos.bmp", NULL);
	vectorMapa[3]= load_bitmap("PuntosGrandes.bmp", NULL);
	vectorMapa[4]= load_bitmap("Espacio.bmp", NULL);
	vectorMapa[6]= load_bitmap("FantasmaBlinky_Abajo.bmp", NULL);
	vectorMapa[8]= load_bitmap("FantasmaInky_Abajo.bmp", NULL);
	vectorMapa[9]= load_bitmap("FantasmaClyde_Abajo.bmp", NULL);
	vectorMapa[7]= load_bitmap("FantasmaPinky_Abajo.bmp", NULL);
    for(int i=0;i<20;i++){
        for(int j=0;j<30;j++){
        	if(matrizJuego[i][j]==0){
        		draw_sprite(buffer, vectorMapa[0], j*30, i*30+35);
			}
			else if(matrizJuego[i][j]==1){
				draw_sprite(buffer, vectorMapa[1], j*30, i*30+35);
			}
			else if(matrizJuego[i][j]==4){
				draw_sprite(buffer, vectorMapa[2], j*30, i*30+35);
			}
			else if(matrizJuego[i][j]==5){
				draw_sprite(buffer, vectorMapa[3], j*30, i*30+35);
			}
			else if(matrizJuego[i][j]==2){
				draw_sprite(buffer, vectorMapa[4], j*30, i*30+35);
			}
			else if(matrizJuego[i][j]==6){
				draw_sprite(buffer, vectorMapa[6], j*30, i*30+35);
			}
			else if(matrizJuego[i][j]==8){
				draw_sprite(buffer, vectorMapa[8], j*30, i*30+35);
			}
			else if(matrizJuego[i][j]==9){
				draw_sprite(buffer, vectorMapa[9], j*30, i*30+35);
			}
			else if(matrizJuego[i][j]==7){
				draw_sprite(buffer, vectorMapa[7], j*30, i*30+35);
			}
        }  
    }
}

void movimientoPacMan(int matrizJuego[20][30], int posPacMan[2]){
    //UP
    if(key[KEY_W]){
        if(matrizJuego[posPacMan[0]-1][posPacMan[1]]!=1){
            matrizJuego[posPacMan[0]][posPacMan[1]]=2;
            posPacMan[0]=posPacMan[0]-1;
            matrizJuego[posPacMan[0]][posPacMan[1]]=0;
        }   
    }
    //DOWN
    else if(key[KEY_S]){
        if(matrizJuego[posPacMan[0]+1][posPacMan[1]]!=1){
            matrizJuego[posPacMan[0]][posPacMan[1]]=2;
            posPacMan[0]=posPacMan[0]+1;
            matrizJuego[posPacMan[0]][posPacMan[1]]=0;
        }
        
    }
    //RIGHT
    else if(key[KEY_D]){//y                  //x
        if(posPacMan[0]==10 && posPacMan[1]==29){
            matrizJuego[posPacMan[0]][posPacMan[1]]=2;
            posPacMan[0]=10;
            posPacMan[1]=0;
            matrizJuego[posPacMan[0]][posPacMan[1]]=0;
            
        }
        else if(matrizJuego[posPacMan[0]][posPacMan[1]+1]!=1){
            matrizJuego[posPacMan[0]][posPacMan[1]]=2;
            posPacMan[1]=posPacMan[1]+1;
            matrizJuego[posPacMan[0]][posPacMan[1]]=0;
        }
	}
    //LEFT
    else if(key[KEY_A]){
        if(posPacMan[0]==10 && posPacMan[1]==0){
            matrizJuego[posPacMan[0]][posPacMan[1]]=2;
            posPacMan[0]=10;
            posPacMan[1]=29;
            matrizJuego[posPacMan[0]][posPacMan[1]]=0;    
        }
        else if(matrizJuego[posPacMan[0]][posPacMan[1]-1]!=1){
            matrizJuego[posPacMan[0]][posPacMan[1]]=2;
            posPacMan[1]=posPacMan[1]-1;
            matrizJuego[posPacMan[0]][posPacMan[1]]=0;
        }
    }   
}
void fantasmaNaranja(int matrizJuego[20][30], int orangeGhost[2]){
	int movement;
	
	//movement= rand()%4;
	movement=3;
	//UP
	if(movement==0){
		if(matrizJuego[orangeGhost[0]-1][orangeGhost[1]]!=1){
			matrizJuego[orangeGhost[0]][orangeGhost[1]]=2; //replace
			orangeGhost[0]=orangeGhost[0]-1;
			matrizJuego[orangeGhost[0]][orangeGhost[1]]=9;			
		}		
	}
	//DOWN
	if(movement==1){
		if(matrizJuego[orangeGhost[0]+1][orangeGhost[1]]!=1){
			matrizJuego[orangeGhost[0]][orangeGhost[1]]=2; //replace
			orangeGhost[0]=orangeGhost[0]+1;
			matrizJuego[orangeGhost[0]][orangeGhost[1]]=9;			
		}		
	}
	//RIGHT
	if(movement==2){
		if(orangeGhost[0]==10 && orangeGhost[1]==29){
			matrizJuego[orangeGhost[0]][orangeGhost[1]]=2;
			orangeGhost[0]=10;
			orangeGhost[1]=0;
			matrizJuego[orangeGhost[0]][orangeGhost[1]]=9;			
		}
		if(matrizJuego[orangeGhost[0]][orangeGhost[1]+1]!=1){
			matrizJuego[orangeGhost[0]][orangeGhost[1]]=2; //replace
			orangeGhost[1]=orangeGhost[1]+1;
			matrizJuego[orangeGhost[0]][orangeGhost[1]]=9;			
		}		
	}
	//LEFT
	if(movement==3){
		if(orangeGhost[0]==10 && orangeGhost[1]==0){
			matrizJuego[orangeGhost[0]][orangeGhost[1]]=2;
			orangeGhost[0]=10;
			orangeGhost[1]=29;
			matrizJuego[orangeGhost[0]][orangeGhost[1]]=9;			
		}
		if(matrizJuego[orangeGhost[0]][orangeGhost[1]-1]!=1){
			matrizJuego[orangeGhost[0]][orangeGhost[1]]=2; //replace
			orangeGhost[1]=orangeGhost[1]-1;
			matrizJuego[orangeGhost[0]][orangeGhost[1]]=9;			
		}		
	}
	
}
	
void fantasmaSalir(int matrizJuego[20][30], int orangeGhost[2], int gNum){
	if(gNum==9){
		matrizJuego[orangeGhost[0]][orangeGhost[1]]=2;
		orangeGhost[0]=10;
		orangeGhost[1]=1;
		matrizJuego[orangeGhost[0]][orangeGhost[1]]=9;	
	}
	
}	
	
	


