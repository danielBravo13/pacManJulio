#include <stdio.h>
#include <allegro.h>

void init();
void motorJuego();
void cargarMapa1(int matrizJuego[20][30]);
void pintarMapa(int matrizJuego[20][30], BITMAP *buffer);
void movimientoPacMan(int matrizJuego[20][30], int posPacMan[2]);


int main(){
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
    int matrizJuego[20][30];
    int pacManPos[2];
    pacManPos[0]=14;
    pacManPos[1]=14;
    cargarMapa1(matrizJuego);
    do{
    	pintarMapa(matrizJuego, buffer);
        //movimientoPacMan(matrizJuego,pacManPos);
        blit(buffer, screen, 0,0,0,0,960,660);
        clear(buffer);
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
			
        }  
    }
}

void movimientoPacMan(int matrizJuego[20][30], int posPacMan[2]){
    
    
    if(key[KEY_W]){
        if(matrizJuego[posPacMan[0]-1][posPacMan[1]]!=1){
            matrizJuego[posPacMan[0]][posPacMan[1]]=2;
            posPacMan[0]=posPacMan[0]-1;
            matrizJuego[posPacMan[0]][posPacMan[1]]=0;
        }   
    }
    else if(key[KEY_S]){
        if(matrizJuego[posPacMan[0]+1][posPacMan[1]]!=1){
            matrizJuego[posPacMan[0]][posPacMan[1]]=2;
            posPacMan[0]=posPacMan[0]+1;
            matrizJuego[posPacMan[0]][posPacMan[1]]=0;
        }
        
    }
    else if(key[KEY_D]){
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

