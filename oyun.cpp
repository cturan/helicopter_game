#include <stdio.h>
#include <gl/glut.h>
#include <iostream>   
#include <time.h>  
#include <string>  
#include <random>  


using namespace std;




float ucakpozX = 0, ucakpozY = 0;
float hel1pozX = 0, hel1pozY = 0;  int hel1renk; int hel1yon; int hel1hiz;
float hel2pozX = 0, hel2pozY = 0;  int hel2renk; int hel2yon; int hel2hiz;
float hel3pozX = 0, hel3pozY = 0;  int hel3renk; int hel3yon; int hel3hiz;
float hel4pozX = 0, hel4pozY = 0;  int hel4renk; int hel4yon; int hel4hiz;

int pervane_donus = 0;
int kullanici_hak = 3;
int kullanici_puan = 0;

std::string oyun_bitti = "";

void pervaneler() {

    if (pervane_donus == 0) {
        pervane_donus = 1;

    }

    else if (pervane_donus == 1) {
        pervane_donus = 2;

    }

    else if (pervane_donus == 2) {
        pervane_donus = 0;
    }

    glutPostRedisplay();
}


void ucak() {

    /*
     * Bu fonksiyon uçağı oluşturmak için gereken çizimleri yapacak
    */


    glColor3f(240, 248, 255);  // rgb renk seçimi --- aliceblue	

    glLineWidth(7);   // uçak kanat ve gövdesi için 7 pixel Çizgi genişliği
    glBegin(GL_LINES); 

    // Uçak kanatları 270 pixelden 320 ye 50 pixel boyutunda
    glVertex2f(270, 60);
    glVertex2f(320, 60);

    // Gövde, 50 pixel uzunluğunda . 
    glVertex2f(295, 80);
    glVertex2f(295, 30);

    // Arka kanat 20 pixel uzunluğunda

    glVertex2f(285, 36);
    glVertex2f(305, 36);
    glEnd(); 

}


void govderenk(int r) {

  if (r == 0) {
      glColor3f(0, 0, 255); //mavi
  }

  if (r == 1) {
      glColor3f(255, 255, 0); // sarı
  }

  if (r == 2) {
      glColor3f(160, 160, 160); // gri
  }

  if (r == 3) {
      glColor3f(255, 204, 204); //pembe
  }

  if (r == 4) {
      glColor3f(51, 0, 25);  // Kahverengi 
  }
}



void helikopter(float x, float y,int yon,int renk) {



    // Gövde
    glBegin(GL_QUAD_STRIP);
    govderenk(renk);
    glVertex2i(x, y);    
    glVertex2i(x, y-30);
    glVertex2i(x+40, y);
    glVertex2i(x+40, y-30);
    glEnd();


    // cam
    glColor3f(0, 191, 255);
    glPointSize(15);
    glBegin(GL_POINTS);

    if (yon == 1) {
        glVertex2i(x + 10, y - 11);
    }
    else {
        glVertex2i(x + 26, y - 11);
    }

    glEnd();

    // Kuyruk 
    glLineWidth(20);
    glBegin(GL_LINES);

    if (yon == 1) {
        glVertex2i(x + 40, y - 15);
        glVertex2i(x + 80, y - 15);
    }
    else {
        glVertex2i(x , y - 15);
        glVertex2i(x -40, y - 15);
    }
    glEnd();


    // Pervane Altı

    glColor3f(0, 191, 255);
    glPointSize(5);
    glBegin(GL_POINTS);
    glVertex2i(x+20, y);
    glEnd();


 
    //üst  pervane 

    glLineWidth(2);
    glBegin(GL_LINES);

    if (pervane_donus == 0) {
        glVertex2i(x-12, y+5);
        glVertex2i(x+51, y+5);
    }

    else if (pervane_donus == 1) {
        glVertex2i(x-12, y-6);
        glVertex2i(x+51, y+12);
    }

    else if  (pervane_donus == 2) {
        glVertex2i(x-12, y+12);
        glVertex2i(x+51, y-6);
    }

    glEnd();

    // Arka pervane 
    glLineWidth(2);
    glColor3f(255, 250, 250);
    glBegin(GL_LINES);


    if (yon == 1) {
        if (pervane_donus == 0) {
            glVertex2i(x + 69, y - 15);
            glVertex2i(x + 89, y - 15);

        }
        else if (pervane_donus == 1) {
            glVertex2i(x + 80, y - 5);
            glVertex2i(x + 80, y - 25);
        }

        else {
            glVertex2i(x + 72, y - 5);
            glVertex2i(x + 88, y - 25);
        }
    }
    else {
        if (pervane_donus == 0) {
            glVertex2i(x - 35, y - 15);
            glVertex2i(x - 50, y - 15);

        }
        else if (pervane_donus == 1) {
            glVertex2i(x - 40, y - 5);
            glVertex2i(x - 40, y - 25);
        }

        else {
            glVertex2i(x - 32, y - 5);
            glVertex2i(x - 48, y - 25);
        }

    }

    glEnd();



    // Gövde altı
    glColor3f(240, 248, 255); 
    glLineWidth(4);  
    glBegin(GL_LINES);

    glVertex2i(x+5, y-30);
    glVertex2i(x+5, y-36);

    glVertex2i(x+35, y-30);
    glVertex2i(x+35, y-36);

    glVertex2i(x, y-37);
    glVertex2i(x+41, y-37);
    glEnd();

}




void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    glColor3f(1.0f, 0.0f, 0.0f);
    glRasterPos2i(400, 460);

    std::string s = "Puan:"+to_string(kullanici_puan)+" Hak:"+to_string(kullanici_hak);
    void* font = GLUT_BITMAP_9_BY_15;

    for (std::string::iterator i = s.begin(); i != s.end(); ++i)
    {
        char c = *i;
        glutBitmapCharacter(font, c);
    }



    glColor3f(1.0f, 0.0f, 0.0f);
    glRasterPos2i(50, 200);
    void* fonts = GLUT_BITMAP_TIMES_ROMAN_24;

    for (std::string::iterator i = oyun_bitti.begin(); i != oyun_bitti.end(); ++i)
    {
        char c = *i;
        glutBitmapCharacter(fonts, c);
    }



    glPushMatrix();
    glTranslated(ucakpozX, ucakpozY, 0);
    ucak();
    glPopMatrix();


    glPushMatrix();
    glTranslated(hel1pozX, hel1pozY, 0);
    helikopter(-50,241,hel1yon,hel1renk);
    glPopMatrix();


    glPushMatrix();
    glTranslated(hel2pozX, hel2pozY, 0);
    helikopter(-50, 310, hel2yon,hel2renk);
    glPopMatrix();


    glPushMatrix();
    glTranslated(hel3pozX, hel3pozY, 0);
    helikopter(-50, 375, hel3yon,hel3renk);
    glPopMatrix();

    glPushMatrix();
    glTranslated(hel4pozX, hel4pozY, 0);
    helikopter(-50, 440, hel4yon,hel4renk);
    glPopMatrix();




    glFlush();
}


void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3d(1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);

}





float hareket_araligi = 13;

void YonTuslari(int key, int x, int y)
{
    switch (key) {
    case GLUT_KEY_RIGHT:

        if (ucakpozX < 320) {
            ucakpozX += hareket_araligi;
        }
        break;

    case GLUT_KEY_LEFT:
        if (ucakpozX > -270) {
            ucakpozX -= hareket_araligi;;
        }
        break;


    case GLUT_KEY_UP:
        ucakpozY += hareket_araligi;;
        break;

    case GLUT_KEY_DOWN:
        if (ucakpozY != 0) {
            ucakpozY -= hareket_araligi;;
            break;
        }

    default:
        break;
    }
    glutPostRedisplay();
}



void OyunuYenidenBaslat() {
    glPushMatrix();
    ucakpozX = 0;
    ucakpozY = 0;
    glTranslated(ucakpozX, ucakpozY, 0);
    ucak();
    glPopMatrix();
}



// Puana göre helikopter hızlarını ayarlayan fonksiyon

// c++ 11 ?

int RastgeleSayi(int a, int b) {
    std::random_device r;
    std::seed_seq seed{ r(), r(), r(), r(), r(), r(), r(), r() };
    std::mt19937 eng(seed);
    std::uniform_int_distribution<> dist{ a,b };
    return dist(eng);
}


void zorluk(int guncel_puan) {

    // Farklı seviyeler

    if (guncel_puan == 0) {
        hel1hiz = RastgeleSayi(1, 3);
        hel2hiz = RastgeleSayi(1, 3);
        hel3hiz = RastgeleSayi(1, 3);
        hel4hiz = RastgeleSayi(1, 3);
    }

    if (guncel_puan >= 10 && guncel_puan < 20) {
        hel1hiz = RastgeleSayi(1, 4);
        hel2hiz = RastgeleSayi(1, 4);
        hel3hiz = RastgeleSayi(1, 4);
        hel4hiz = RastgeleSayi(1, 4);
    }

    if (guncel_puan >= 20 && guncel_puan < 30) {
        hel1hiz = RastgeleSayi(1, 5);
        hel2hiz = RastgeleSayi(1, 5);
        hel3hiz = RastgeleSayi(1, 5);
        hel4hiz = RastgeleSayi(1, 5);
    }

    if (guncel_puan >= 30 && guncel_puan < 40) {
        hel1hiz = RastgeleSayi(1, 6);
        hel2hiz = RastgeleSayi(1, 6);
        hel3hiz = RastgeleSayi(1, 6);
        hel4hiz = RastgeleSayi(1, 6);
    }

    if (guncel_puan >= 50 && guncel_puan < 60) {
        hel1hiz = RastgeleSayi(2, 7);
        hel2hiz = RastgeleSayi(2, 7);
        hel3hiz = RastgeleSayi(2, 7);
        hel4hiz = RastgeleSayi(2, 7);
    }

    if (guncel_puan >= 60 && guncel_puan < 70) {
        hel1hiz = RastgeleSayi(3, 8);
        hel2hiz = RastgeleSayi(3, 8);
        hel3hiz = RastgeleSayi(3, 8);
        hel4hiz = RastgeleSayi(3, 8);
    }

    if (guncel_puan >= 70 && guncel_puan < 80) {
        hel1hiz = RastgeleSayi(3, 9);
        hel2hiz = RastgeleSayi(3, 9);
        hel3hiz = RastgeleSayi(3, 9);
        hel4hiz = RastgeleSayi(3, 9);
    }


    if (guncel_puan >= 80) {
        hel1hiz = RastgeleSayi(3, 15);
        hel2hiz = RastgeleSayi(3, 15);
        hel3hiz = RastgeleSayi(3, 15);
        hel4hiz = RastgeleSayi(3, 15);
    }


}



// Glut ile enter tuşunu dinlemek ve gerektiğinde bu tuşla oyunu yeniden başlatmak için gereken fonksiyon.


void Enter_tusu(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 13:  // enter tuşunun ascii kodu

        // Enter tuşuna basıldığında kullanıcının oyunu kaybettiğini doğruluyoruz ve oyunu yeniden başlatıyoruz.
        if (kullanici_hak == 0) {
            kullanici_hak = 3;
            kullanici_puan = 0;
            zorluk(kullanici_puan);
            oyun_bitti = "";
            OyunuYenidenBaslat();
        }
        break;
    }

}



void OyunBitti() {



    oyun_bitti = "Kaybettin :( yeniden baslamak icin entera bas ";
}



void carpismatespiti() {


    // İlk helikopterin çarpışma alanları

    if (ucakpozY+30 > 150) {
        if (ucakpozY+30 < 250) {


            if (ucakpozX + 270 > hel1pozX) {
                int fark = ((ucakpozX + 270) - hel1pozX);

                // Uçağa soldan gelen darbeler
                if (fark >= 1  && fark < 8) {
                   if (kullanici_hak > 0) {
                       OyunuYenidenBaslat();
                       kullanici_hak -= 1;
                   }
                   else {
                       OyunBitti();
                   }
                   
                }
                
            }
            else {
                int fark = (hel1pozX - (ucakpozX + 270));
                
                // Uçağa sağdan gelen darbeler
                if (fark <= 104 && fark > 1) {
                    if (kullanici_hak > 0) {
                        OyunuYenidenBaslat();
                        kullanici_hak -= 1;
                    }
                    else {
                        OyunBitti();
                    }
                    

                }

                
            }

        }  
    }


    // 2. helikopterin çarpışma alanları

    if (ucakpozY + 30 > 220) {
        if (ucakpozY + 30 < 320) {


            if (ucakpozX + 270 > hel2pozX) {
                int fark = ((ucakpozX + 270) - hel2pozX);

                // Uçağa soldan gelen darbeler
                if (fark >= 1 && fark < 8) {
                    if (kullanici_hak > 0) {
                        OyunuYenidenBaslat();
                        kullanici_hak -= 1;
                    }
                    else {
                        OyunBitti();
                    }

                }

            }
            else {
                int fark = (hel2pozX - (ucakpozX + 270));

                // Uçağa sağdan gelen darbeler
                if (fark <= 104 && fark > 1) {
                    if (kullanici_hak > 0) {
                        OyunuYenidenBaslat();
                        kullanici_hak -= 1;
                    }
                    else {
                        OyunBitti();
                    }


                }


            }

        }
    }


    // 3. helikopterin çarpışma alanları

    if (ucakpozY + 30 > 280) {
        if (ucakpozY + 30 < 380) {


            if (ucakpozX + 270 > hel3pozX) {
                int fark = ((ucakpozX + 270) - hel3pozX);

                // Uçağa soldan gelen darbeler
                if (fark >= 1 && fark < 8) {
                    if (kullanici_hak > 0) {
                        OyunuYenidenBaslat();
                        kullanici_hak -= 1;
                    }
                    else {
                        OyunBitti();
                    }

                }

            }
            else {
                int fark = (hel3pozX - (ucakpozX + 270));

                // Uçağa sağdan gelen darbeler
                if (fark <= 104 && fark > 1) {
                    if (kullanici_hak > 0) {
                        OyunuYenidenBaslat();
                        kullanici_hak -= 1;
                    }
                    else {
                        OyunBitti();
                    }


                }


            }

        }
    }



    // 4. helikopterin çarpışma alanları

    if (ucakpozY + 30 > 350) {
        if (ucakpozY + 30 < 450) {


            if (ucakpozX + 270 > hel4pozX) {
                int fark = ((ucakpozX + 270) - hel4pozX);

                // Uçağa soldan gelen darbeler
                if (fark >= 1 && fark < 8) {
                    if (kullanici_hak > 0) {
                        OyunuYenidenBaslat();
                        kullanici_hak -= 1;
                    }
                    else {
                        OyunBitti();
                    }

                }

            }
            else {
                int fark = (hel4pozX - (ucakpozX + 270));

                // Uçağa sağdan gelen darbeler
                if (fark <= 104 && fark > 1) {
                    if (kullanici_hak > 0) {
                        OyunuYenidenBaslat();
                        kullanici_hak -= 1;
                    }
                    else {
                        OyunBitti();
                    }


                }


            }

        }
    }


    // Başarılı Kaçış.

    if (ucakpozY + 30 > 455) {
        kullanici_puan += 10;
        zorluk(kullanici_puan);
        OyunuYenidenBaslat();
    }
  

}


void timer(int extra)
{
    glutTimerFunc(30, timer, 0);
    pervaneler();
    carpismatespiti();
}






void timer3(int extra) {


    // 1. Helikopter

    if (hel1yon == 0) {
        if (hel1pozX < 750) {
            hel1pozX += hel1hiz;
        }
        else {
            hel1pozX = -100;
        }
    }
    else {
        if (hel1pozX > -100) {
            hel1pozX -= hel1hiz;
        }
        else {
            hel1pozX = 750;
        }
    }

    // 2. Helikopter

    if (hel2yon == 0) {
        if (hel2pozX < 750) {
            hel2pozX += hel2hiz;
        }
        else {
            hel2pozX = -100;
        }
    }
    else {
        if (hel2pozX > -100) {
            hel2pozX -= hel2hiz;
        }
        else {
            hel2pozX = 750;
        }
    }

    // 3. Helikopter

    if (hel3yon == 0) {
        if (hel3pozX < 750) {
            hel3pozX += hel3hiz;
        }
        else {
            hel3pozX = -100;
        }
    }
    else {
        if (hel3pozX > -100) {
            hel3pozX -= hel3hiz;
        }
        else {
            hel3pozX = 750;
        }
    }


    // 4. Helikopter 

    if (hel4yon == 0) {
        if (hel4pozX < 750) {
            hel4pozX += hel4hiz;
        }
        else {
            hel4pozX = -100;
        }
    }
    else {
        if (hel4pozX > -100) {
            hel4pozX -= hel4hiz;
        }
        else {
            hel4pozX = 750;
        }
    }

    glutTimerFunc(10, timer3, 0);
}






int main(int argc, char** argv) {

    srand(time(0));

    hel1renk = rand() % 5; hel1yon = rand() % 2;  
    hel2renk = rand() % 5; hel2yon = rand() % 2;
    hel3renk = rand() % 5; hel3yon = rand() % 2;
    hel4renk = rand() % 5; hel4yon = rand() % 2;

    zorluk(kullanici_puan); // ilk çalışma

    glDisable(GL_LIGHTING);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Oyun programi");
    glutDisplayFunc(display);
    init();
    glutTimerFunc(0, timer, 0);
    glutTimerFunc(0, timer3, 0);
    glutSpecialFunc(YonTuslari);
    glutKeyboardFunc(Enter_tusu);
    glutMainLoop();

}