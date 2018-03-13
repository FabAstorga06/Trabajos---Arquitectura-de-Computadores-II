#include "encrypt_algs.c"


extern unsigned int img_h, img_w, img_channels;

/*********************************************************************************/

IplImage* convert2gray(char* img_name ) {

  IplImage* img_proc = 0;
  // Carga una imagen
  img_proc = cvLoadImage(img_name, CV_LOAD_IMAGE_COLOR );
  // Verifica si la imagen se cargo exitosamente
  if(!img_proc ) {
    printf("No fue posible cargar la imagen: %s\n",img_name);
    exit(0);
  }

  img_h = img_proc->height;
  img_w = img_proc->width;
  img_channels = img_proc->nChannels;
  printf("Procesando imagen de %dx%d con %d canales.\n",img_h,
                                            img_w,img_channels);
  // Crea ventana para mostrar imagen
  cvNamedWindow(TITLE_W, CV_WINDOW_AUTOSIZE);
  cvMoveWindow(TITLE_W, SIZE_W, SIZE_W);
  // Se crea un objeto que será la nueva imagen gris
  IplImage* img_gray = cvCreateImage(cvSize(img_w, img_h),
                                            IPL_DEPTH_8U, 1);
  // Cambia escala de imagen de RGB a gris
  cvCvtColor(img_proc, img_gray, CV_RGB2GRAY);
  return img_gray;
}

void show_image (IplImage* img) {
  // Muestra la imagen
  cvShowImage(TITLE_W, img );
  // Espera por una señal del teclado para cerrar ventana
  cvWaitKey(0);
}

/*********************************************************************************/

int main(int argc, char* argv[] )  {

  // Verifica si se inserto el nombre de la imagen al ejecutar
  if (argc < 2 ) {
    printf("Inserte el nombre de la imagen...\n\7");
    exit(0);
  }

  /* SE MUESTRA IMAGEN EN ESCALA DE GRISES */
  // Se convierte imagen a escala de grises
  IplImage* img_g = convert2gray(argv[1] );
  show_image(img_g);

  /* SE ENCRIPTA IMAGEN */
  /* Se cambia de imagen a matriz */
  CvMat* mtx_g = cvCreateMat(img_h, img_w, CV_8UC1 );
  cvConvert( img_g, mtx_g );

  /* Encriptacion con XOR */
//  printf("----ENCRYPT XOR----\n");
//  xor_encrypt(mtx_g);
  /* Desencripta con XOR */
//  printf("----DECRYPT XOR----\n");
//  xor_encrypt(mtx_g);

  /* Encriptacion con desplazamiento simple */
  printf("----ENCRYPT SIMPLE DISPLACE----\n");
  simple_desp(mtx_g);
  /* Desencripta con desplazamiento simple (se pierde info) */
  printf("----DECRYPT SIMPLE DISPLACE----\n");
  decrypt_simple_desp(mtx_g);


  // circular_desp(mtx_g, img_g->height, img_g->width);


/* TOMAR EN CUENTA EL DESBORDAMIENTO **** */
//  printf("----ENCRYPT SIMPLE ADD----\n");
//  simple_add(mtx_g);
//  printf("----DECRYPT SIMPLE ADD----\n");
//  simple_add_decrypt(mtx_g);

  return 0;
}