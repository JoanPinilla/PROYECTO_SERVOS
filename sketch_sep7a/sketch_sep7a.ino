// CONEXIONES!
// Pines de driver
const int pin_IN1 = 12; // Pin para sentido del motor 1
const int pin_IN2 = 8; // Pin para sentido del motor 1
const int pin_IN3 = 7; // Pin para sentido del motor 2
const int pin_IN4 = 4; // Pin para sentido del motor 2
const int pin_ENA = 11; // Pin PWM para motor 1
const int pin_ENB = 3; // Pin PWM para motor 2

// Pines de sensores
const int pin_SM1 = A0; // Recibe la información análoga del encoder del motor 1
const int pin_SM2 = A1; // Recibe la información análoga del encoder del motor 2
const int pin_FC1 = 2; // Pin del final de carrera 1
const int pin_FC2 = 5; // Pin del final de carrera 2

// VARIABLES!
int estado_FC1; // Estado del final de carrera 1
int estado_FC2; // Estado del final de carrera 1
int lim_FC1; // Posición raw del límite inferior para el brazo 2.
int lim_FC2; // Posición raw del límite superior para el brazo 2.
double raw_ANG1; // Recibe la lectura "raw" del sensor 1
double raw_ANG2; // Recibe la lectura "raw" del sensor 1
float ANG1; // Valor del sensor 1 convertido a grados.
double ANG2; // Valor del sensor 1 convertido a grados.

int lim_inf_M2; // Límite inferior del rango de movimiento del M2.
int lim_sup_M2; // Límite superior del rango de movimiento del M2.
float factor_escala; // Para la conversión de 0-1024 a grados
float rango_total_grados; // Para la conversión de 0-1024 a grados

double offset_S2; // Establece el offset de lectura para el Sensor 2.

// TRAYECTORIA
float TRAYEC[][2] = {
{ 90.986062 , -68.890023 },
{ 89.181396 , -65.708980 },
{ 87.338968 , -62.431191 },
{ 85.462526 , -59.063015 },
{ 83.555978 , -55.611352 },
{ 81.623220 , -52.083306 },
{ 79.668287 , -48.486446 },
{ 77.695437 , -44.828932 },
{ 75.709407 , -41.119996 },
{ 73.715816 , -37.370703 },
{ 71.721291 , -33.594221 },
{ 69.734584 , -29.808003 },
{ 67.767929 , -26.036498 },
{ 65.840209 , -22.317443 },
{ 63.982735 , -18.713447 },
{ 62.253041 , -15.339528 },
{ 60.763205 , -12.419766 },
{ 59.725438 , -10.378489 },
{ 59.436312 , -9.808689 },
{ 60.020406 , -10.959312 },
{ 61.262955 , -13.400580 },
{ 62.883766 , -16.571798 },
{ 64.710140 , -20.127183 },
{ 66.653401 , -23.888951 },
{ 68.667502 , -27.764501 },
{ 70.726603 , -31.701588 },
{ 72.814941 , -35.668065 },
{ 72.790398 , -35.621607 },
{ 72.706699 , -35.463144 },
{ 72.622659 , -35.303991 },
{ 72.538273 , -35.144138 },
{ 72.453536 , -34.983575 },
{ 72.290781 , -34.675055 },
{ 70.208597 , -30.713555 },
{ 68.159022 , -26.788344 },
{ 66.159581 , -22.935095 },
{ 64.240085 , -19.213964 },
{ 62.454252 , -15.732887 },
{ 60.907481 , -12.703069 },
{ 59.800477 , -10.526296 },
{ 59.425094 , -9.786571 },
{ 59.926090 , -10.773648 },
{ 61.103690 , -13.088159 },
{ 62.668713 , -16.151896 },
{ 64.437987 , -19.598602 },
{ 66.317043 , -23.239401 },
{ 68.256785 , -26.976145 },
{ 70.229926 , -30.754271 },
{ 72.219605 , -34.540081 },
{ 74.214567 , -38.311105 },
{ 76.206872 , -42.051503 },
{ 78.190041 , -45.748441 },
{ 80.158877 , -49.391689 },
{ 82.108673 , -52.972116 },
{ 84.035265 , -56.481783 },
{ 85.934603 , -59.913144 },
{ 87.802899 , -63.259345 },
{ 89.636255 , -66.513564 },
{ 91.430854 , -69.669387 },
{ 92.785726 , -72.031655 },
{ 94.112862 , -74.327931 },
{ 95.414665 , -76.562783 },
{ 96.694442 , -78.742203 },
{ 97.955141 , -80.871422 },
{ 99.198164 , -82.952944 },
{ 99.847359 , -84.032806 },
{ 100.596847 , -85.273141 },
{ 101.438307 , -86.657397 },
{ 102.363133 , -88.168438 },
{ 103.362492 , -89.788737 },
{ 104.427480 , -91.500722 },
{ 105.549288 , -93.287117 },
{ 106.719042 , -95.130776 },
{ 107.928073 , -97.015185 },
{ 109.167865 , -98.924462 },
{ 110.429914 , -100.843198 },
{ 111.705919 , -102.756844 },
{ 112.987512 , -104.651352 },
{ 114.266441 , -106.513538 },
{ 115.534377 , -108.330852 },
{ 116.782920 , -110.091442 },
{ 118.003569 , -111.784163 },
{ 119.187682 , -113.398549 },
{ 120.326470 , -114.924815 },
{ 121.411016 , -116.353854 },
{ 122.432285 , -117.677209 },
{ 123.381221 , -118.887104 },
{ 124.248808 , -119.976394 },
{ 125.026210 , -120.938575 },
{ 125.704910 , -121.767752 },
{ 126.276902 , -122.458645 },
{ 127.393483 , -123.786262 },
{ 128.523895 , -125.101649 },
{ 129.669568 , -126.405029 },
{ 130.831934 , -127.696490 },
{ 132.012523 , -128.976079 },
{ 133.212965 , -130.243802 },
{ 134.994815 , -132.063179 },
{ 136.807713 , -133.837677 },
{ 138.643629 , -135.556171 },
{ 140.493267 , -137.208151 },
{ 142.345833 , -138.783841 },
{ 144.188764 , -140.274257 },
{ 146.007541 , -141.671312 },
{ 147.785532 , -142.967862 },
{ 149.504007 , -144.157788 },
{ 151.142254 , -145.236009 },
{ 152.677933 , -146.198487 },
{ 154.087578 , -147.042163 },
{ 155.347329 , -147.764859 },
{ 156.433833 , -148.365136 },
{ 157.325207 , -148.842083 },
{ 158.002112 , -149.195127 },
{ 158.448699 , -149.423796 },
{ 158.653490 , -149.527539 },
{ 158.609987 , -149.505560 },
{ 158.317059 , -149.356740 },
{ 157.779005 , -149.079627 },
{ 157.005306 , -148.672502 },
{ 156.010087 , -148.133522 },
{ 154.811322 , -147.460911 },
{ 153.429871 , -146.653188 },
{ 151.888400 , -145.709389 },
{ 151.954477 , -145.750785 },
{ 152.021171 , -145.792481 },
{ 152.087278 , -145.833725 },
{ 152.154161 , -145.875368 },
{ 152.221140 , -145.916982 },
{ 152.287495 , -145.958124 },
{ 153.791144 , -146.867850 },
{ 155.128993 , -147.641678 },
{ 156.278733 , -148.280728 },
{ 157.220119 , -148.786570 },
{ 157.936069 , -149.161025 },
{ 158.413532 , -149.405911 },
{ 158.644296 , -149.522897 },
{ 158.625406 , -149.513354 },
{ 158.359352 , -149.378316 },
{ 157.853923 , -149.118505 },
{ 157.121767 , -148.734443 },
{ 156.179680 , -148.226600 },
{ 155.047737 , -147.595616 },
{ 153.748289 , -146.842515 },
{ 152.304902 , -145.968903 },
{ 150.741408 , -144.977162 },
{ 149.081066 , -143.870597 },
{ 147.345847 , -142.653500 },
{ 145.555987 , -141.331211 },
{ 143.729695 , -139.910107 },
{ 141.883068 , -138.397574 },
{ 140.030133 , -136.801939 },
{ 138.182974 , -135.132382 },
{ 136.351997 , -133.398878 },
{ 134.546149 , -131.612092 },
{ 132.773200 , -129.783307 },
{ 131.628393 , -128.563303 },
{ 130.501720 , -127.332783 },
{ 129.390944 , -126.090824 },
{ 128.295203 , -124.837879 },
{ 127.213694 , -123.574386 },
{ 126.144322 , -122.299153 },
{ 125.544936 , -121.573226 },
{ 124.840787 , -120.710278 },
{ 124.040027 , -119.715748 },
{ 123.151265 , -118.595671 },
{ 122.183394 , -117.356712 },
{ 121.145457 , -116.006181 },
{ 120.046508 , -114.552019 },
{ 118.895561 , -113.002847 },
{ 117.701493 , -111.367929 },
{ 116.473065 , -109.657233 },
{ 115.218882 , -107.881391 },
{ 113.947415 , -106.051724 },
{ 112.667038 , -104.180248 },
{ 111.386052 , -102.279666 },
{ 110.112766 , -100.363429 },
{ 108.855484 , -98.445642 },
{ 107.622598 , -96.541138 },
{ 106.422569 , -94.665380 },
{ 105.264005 , -92.834502 },
{ 104.155562 , -91.065078 },
{ 103.106148 , -89.374377 },
{ 102.124567 , -87.779707 },
{ 101.219794 , -86.298783 },
{ 100.400508 , -84.948883 },
{ 99.675350 , -83.747181 },
{ 98.290744 , -81.435183 },
{ 96.885535 , -79.066090 },
{ 95.455897 , -76.633277 },
{ 93.998791 , -74.131263 },
{ 92.510702 , -71.553590 },
{ 90.986062 , -68.890023 },
};

float RECTA[][2] = {
{ 86.081081 , -53.327026 },
{ 84.644084 , -51.594245 },
{ 83.273126 , -50.022210 },
{ 81.980891 , -48.630410 },
{ 80.779993 , -47.438281 },
{ 79.682296 , -46.463884 },
{ 78.698512 , -45.723028 },
{ 77.837767 , -45.228473 },
{ 77.107083 , -44.988723 },
{ 76.511223 , -45.007779 },
{ 76.052185 , -45.284099 },
{ 75.729544 , -45.811263 },
{ 75.540577 , -46.578194 },
{ 75.480767 , -47.570120 },
{ 75.544104 , -48.769159 },
{ 75.723862 , -50.155856 },
{ 76.012928 , -51.709868 },
{ 76.404091 , -53.410494 },
{ 76.890487 , -55.237472 },
{ 77.465832 , -57.171570 },
{ 78.124335 , -59.194343 },
{ 78.860849 , -61.288417 },
{ 79.670927 , -63.437611 },
{ 80.550672 , -65.626687 },
{ 81.496756 , -67.841404 },
{ 82.506279 , -70.068301 },
{ 83.576664 , -72.294446 },
{ 83.772160 , -73.588112 },
{ 83.918026 , -74.806543 },
{ 84.043110 , -75.998435 },
{ 84.147765 , -77.164729 },
{ 84.232296 , -78.306274 },
{ 84.238751 , -79.064529 },
{ 83.511285 , -79.275732 },
{ 82.871588 , -79.617552 },
{ 82.320775 , -80.086546 },
{ 81.859676 , -80.678427 },
{ 81.488658 , -81.387893 },
{ 81.207934 , -82.208969 },
{ 81.017340 , -83.134804 },
{ 80.916602 , -84.157992 },
{ 80.905321 , -85.270585 },
{ 80.983002 , -86.464151 },
{ 81.149022 , -87.729772 },
{ 81.402809 , -89.058264 },
{ 81.743739 , -90.440108 },
{ 82.171151 , -91.865482 },
{ 82.684413 , -93.324389 },
{ 83.282762 , -94.806512 },
{ 83.965330 , -96.301315 },
{ 84.731181 , -97.798151 },
{ 85.578985 , -99.285997 },
{ 86.507147 , -100.753712 },
{ 87.513501 , -102.189857 },
{ 88.595327 , -103.582876 },
{ 89.749043 , -104.920971 },
{ 90.970182 , -106.192325 },
{ 92.253036 , -107.384964 },
{ 93.590638 , -108.487026 },
{ 94.431822 , -109.899326 },
{ 95.271842 , -111.299255 },
{ 96.110539 , -112.686790 },
{ 96.948783 , -114.062724 },
{ 97.787457 , -115.427811 },
{ 98.626390 , -116.781884 },
{ 98.759580 , -118.126635 },
{ 98.982574 , -119.480483 },
{ 99.298495 , -120.836594 },
{ 99.710500 , -122.187777 },
{ 100.221602 , -123.526384 },
{ 100.834550 , -124.844328 },
{ 101.551732 , -126.133103 },
{ 102.374738 , -127.383620 },
{ 103.304304 , -128.586384 },
{ 104.339938 , -129.731474 },
{ 105.479412 , -130.808506 },
{ 106.718586 , -131.806879 },
{ 108.050759 , -132.715738 },
{ 109.466531 , -133.524317 },
{ 110.953362 , -134.222061 },
{ 112.495460 , -134.798925 },
{ 114.073840 , -135.245684 },
{ 115.666591 , -135.554241 },
{ 117.249438 , -135.717934 },
{ 118.796560 , -135.731807 },
{ 120.281580 , -135.592801 },
{ 121.678735 , -135.299884 },
{ 122.963945 , -134.854054 },
{ 124.115849 , -134.258255 },
{ 125.116549 , -133.517193 },
{ 125.952131 , -132.637112 },
{ 127.209103 , -132.671441 },
{ 128.455296 , -132.682505 },
{ 129.689706 , -132.669687 },
{ 130.911134 , -132.633332 },
{ 132.118440 , -132.573827 },
{ 133.310529 , -132.490581 },
{ 135.058562 , -133.206547 },
{ 136.803234 , -133.774615 },
{ 138.521992 , -134.190723 },
{ 140.190918 , -134.452621 },
{ 141.785719 , -134.560040 },
{ 143.282749 , -134.514727 },
{ 144.660068 , -134.320404 },
{ 145.898333 , -133.982633 },
{ 146.981524 , -133.508593 },
{ 147.897373 , -132.906816 },
{ 148.637541 , -132.186863 },
{ 149.197514 , -131.359032 },
{ 149.576315 , -130.434056 },
{ 149.776082 , -129.422860 },
{ 149.801543 , -128.336331 },
{ 149.659508 , -127.185170 },
{ 149.358345 , -125.979750 },
{ 148.907540 , -124.730048 },
{ 148.317293 , -123.445592 },
{ 147.598196 , -122.135431 },
{ 146.760975 , -120.808142 },
{ 145.816292 , -119.471826 },
{ 144.774602 , -118.134144 },
{ 143.646050 , -116.802337 },
{ 142.440401 , -115.483243 },
{ 141.167002 , -114.183339 },
{ 140.617083 , -112.806213 },
{ 140.056677 , -111.417526 },
{ 139.485077 , -110.016388 },
{ 138.903284 , -108.603222 },
{ 138.310753 , -107.177041 },
{ 137.707053 , -105.737152 },
{ 137.783639 , -104.517435 },
{ 137.720912 , -103.217602 },
{ 137.525103 , -101.849590 },
{ 137.203527 , -100.425318 },
{ 136.764386 , -98.956685 },
{ 136.216442 , -97.455317 },
{ 135.568987 , -95.932835 },
{ 134.831511 , -94.400495 },
{ 134.013745 , -92.869531 },
{ 133.125429 , -91.350897 },
{ 132.176292 , -89.855384 },
{ 131.175937 , -88.393544 },
{ 130.133882 , -86.975850 },
{ 129.059399 , -85.612451 },
{ 127.961528 , -84.313260 },
{ 126.849074 , -83.087981 },
{ 125.730535 , -81.945964 },
{ 124.614029 , -80.896088 },
{ 123.507337 , -79.946846 },
{ 122.417814 , -79.106143 },
{ 121.352338 , -78.381187 },
{ 120.317316 , -77.778488 },
{ 119.318549 , -77.303562 },
{ 118.361346 , -76.961153 },
{ 117.450327 , -76.754779 },
{ 116.589532 , -76.686967 },
{ 115.573167 , -75.563509 },
{ 114.552386 , -74.417142 },
{ 113.525661 , -73.245575 },
{ 112.492927 , -72.048545 },
{ 111.454082 , -70.825748 },
{ 110.407375 , -69.574534 },
{ 109.169904 , -67.297029 },
{ 107.879309 , -65.027700 },
{ 106.546049 , -62.779749 },
{ 105.181006 , -60.567353 },
{ 103.795468 , -58.405638 },
{ 102.401214 , -56.310883 },
{ 101.010481 , -54.300469 },
{ 99.636093 , -52.393149 },
{ 98.291378 , -50.608901 },
{ 96.990111 , -48.968767 },
{ 95.746337 , -47.494527 },
{ 94.574100 , -46.208119 },
{ 93.487024 , -45.130784 },
{ 92.497972 , -44.282419 },
{ 91.618260 , -43.679869 },
{ 90.857255 , -43.336225 },
{ 90.221887 , -43.259767 },
{ 89.716124 , -43.452880 },
{ 89.341188 , -43.912492 },
{ 89.095392 , -44.629737 },
{ 88.974965 , -45.591468 },
{ 88.974148 , -46.780640 },
{ 89.086104 , -48.177809 },
{ 89.303311 , -49.762261 },
{ 89.618211 , -51.512896 },
{ 89.085031 , -51.917640 },
{ 88.528573 , -52.280160 },
{ 87.949391 , -52.602083 },
{ 87.348077 , -52.883599 },
{ 86.725223 , -53.124878 },
{ 86.081081 , -53.327026 },
};


void setup() {
  // Establecer pines como salidas o entradas:
  pinMode(pin_IN1, OUTPUT);
  pinMode(pin_IN2, OUTPUT);
  pinMode(pin_IN3, OUTPUT);
  pinMode(pin_IN4, OUTPUT);
  pinMode(pin_ENA, OUTPUT);
  pinMode(pin_ENB, OUTPUT);

  pinMode(pin_SM1, INPUT);
  pinMode(pin_SM2, INPUT);
  pinMode(pin_FC1, INPUT);
  pinMode(pin_FC2, INPUT);

  Serial.begin(115200); // Inicializar comunicación serial
  // home(); //TODO: Cambiar función
  offset_S2 = calib(); // Establece el valor del offset con una primera lectura.
}

void loop() {
  digitalWrite(pin_IN1, LOW);
  digitalWrite(pin_IN2, HIGH);
  // Serial.print(millis());
  if (digitalRead(13)){
    analogWrite(pin_ENA, 100);
    delay(100);
    analogWrite(pin_ENA, 0);
  }

  // double T0 = millis(); // Tiempo de inicio del ciclo
  // for (int i = 0; i < 192; i++){ // Ciclo para recorrer cada posición en la trayectoria.
  //   llevar(TRAYEC[i][0], TRAYEC[i][1]);
  // }
  // double T1 = millis(); // Tiempo de finalización del ciclo.
  // Serial.println("RECORRIDO TERMINADO EN: ");
  // Serial.println((T1-T0)/1000); // Imprime el tiempo que tardó el brazo en completar el trébol.
  // delay(5000);

  // ********** DEBUG *********

  //**** LEER SENSORES ****
  Serial.print(analogRead(pin_SM1));
  Serial.print("\t");
  Serial.print(leer_S1());
  Serial.print("\t");
  Serial.println(analogRead(pin_SM2));

  // **** VER ESTADO DE FINALES DE CARRERA ****
  // Serial.print(debounce_FC(pin_FC1));
  // Serial.print(" \t ");
  // Serial.println(debounce_FC(pin_FC2));
}


/**
 * @brief Realiza una primera lectura de la posicón del M2.
 */
double calib (){
  double pos_ini = analogRead(pin_SM2);
  // Serial.print("Pos. inicial: ");
  // Serial.println(pos_ini);
  return pos_ini;
}

/**
 * @brief Lleva los brazos a la posición de inicio.
 */
void home(){
  float pos_ini1 = leer_S1(); // Posición inicial para el motor 1.
  float pos_ini2 = leer_S2(); // Posición inicial para el motor 2.
  if (pos_ini1 > 90){
  // Sentido horario MOTOR 1 - CW
  digitalWrite(pin_IN1, LOW);
  digitalWrite(pin_IN2, HIGH);
  } else if (pos_ini1 < 90){
  // Sentido antihorario MOTOR 1 - CCW
  digitalWrite(pin_IN1, HIGH);
  digitalWrite(pin_IN2, LOW);
  }
  do{
    digitalWrite(pin_ENA, 55);
  } while(leer_S1() != 90);
  digitalWrite(pin_ENA, 0);
  
  // HOMING DEL M2
  do{
    // Sentido horario MOTOR 2 - CW
    digitalWrite(pin_IN3, LOW);
    digitalWrite(pin_IN4, HIGH);
    digitalWrite(pin_ENB, 255);
    Serial.print("raw_ANG2: ");
    Serial.println(analogRead(pin_SM2));
  } while(debounce_FC(pin_FC1) == 0);
  digitalWrite(pin_ENB, 0);
  lim_inf_M2 = analogRead(pin_SM2);
  Serial.print("Posición inicial del M2: ");
  Serial.println(lim_inf_M2);
  do{
    // Sentido antihorario MOTOR 2 - CCW
    digitalWrite(pin_IN3, !LOW);
    digitalWrite(pin_IN4, !HIGH);
    digitalWrite(pin_ENB, 255);
    Serial.print("raw_ANG2: ");
    Serial.println(analogRead(pin_SM2));
  } while(debounce_FC(pin_FC2) == 0);
  digitalWrite(pin_ENB, 0);
  lim_sup_M2 = analogRead(pin_SM2);
  rango_total_grados = (1024 - abs(lim_inf_M2 - lim_sup_M2))*360.0/1024.0;
  factor_escala = rango_total_grados/1024.0;
  Serial.print("Posición inicial del M2: ");
  Serial.println(lim_inf_M2);
  Serial.print("Posición final del M2: ");
  Serial.println(lim_sup_M2);
  Serial.print("Rango total en grados: ");
  Serial.println(rango_total_grados);
  delay(2000);
}

/**
 * @brief Lee la salida análoga del sensor 1 y la convierte a grados.
 * 
 * @return Posición angular en grados del eje del motor 1. 
 */
float leer_S1(){
  raw_ANG1 = analogRead(pin_SM1); // Lee el sensor del motor 1.
  ANG1 = (raw_ANG1-285.0)*180.0/(755.0-285.0);
  // Serial.print(ANG1);
  return ANG1;
}

/**
 * @brief Lee la salida análoga del sensor 2 y la convierte a grados.
 * 
 * @return Posición angular en grados del eje del motor 2. 
 */
float leer_S2(){ 
  raw_ANG2 = analogRead(pin_SM2); // Lee el sensor del motor 2.
  ANG2 = (raw_ANG2 - offset_S2)*(360.0/1024.0); // Se convierte el valor del sensor a grados y se le aplica el offset.
  //Serial.println(raw_ANG2 - lim_inf_M2);
  //ANG2 = (raw_ANG2 - lim_inf_M2)*factor_escala;// + lim_inf_M2*(360/1024.0);// rango_total_grados/2.0; // - min(lim_inf_M2, lim_sup_M2)*(360.0/1024.0); // Posición del motor 2 en grados.
  //ANG2 = ANG2 + ((1024-lim_inf_M2) + lim_sup_M2)/2*(360.0/1024.0)
  //Serial.print(ANG2);
  //Serial.print(" - ");
  //Serial.println(offset_S2);
  //return (ANG2*(360.0/1024.0));
  return ANG2;
}


/**
 * @brief Lleva los brazos a una posición de referencia indicada aplicando control proporcional.
 * 
 * @param ref_M1 [°] Posición angular a la cual se desea llevar el brazo 1.
 * @param ref_M2 [°] Posición angular a la cual se desea llevar el brazo 2.
 */
void llevar(float ref_M1, float ref_M2){
  float pos_actualM1 = leer_S1(); // Obtiene la posición actual del motor 1
  float pos_actualM2 = leer_S2(); // Obtiene la posición actual del motor 2
  float error_M1; // Error de posición para el Motor 1.
  float error_M2; // Error de posición para el Motor 2.
  float KP = 1; // Constante de ganancia proporcional para el motor 1
  float KP2 = 5; // Constante de ganancia proporcional para el motor 2
  int PWM_M1;
  int PWM_M2;
  do{
    error_M1 = ref_M1 - pos_actualM1; // Calcula el error de posición para el motor 1.
    error_M2 = ref_M2 - pos_actualM2; // Calcula el error de posición para el motor 2.
    if (pos_actualM1 > ref_M1  && pos_actualM2 > ref_M2){ // Se establece el sentido de movimiento para los motores de acuerdo a la referencia.
      digitalWrite(pin_IN1, LOW);
      digitalWrite(pin_IN2, HIGH);
      digitalWrite(pin_IN3, LOW);
      digitalWrite(pin_IN4, HIGH);
    } else if (pos_actualM1 < ref_M1  && pos_actualM2 < ref_M2){ // Se establece el sentido de movimiento para los motores de acuerdo a la referencia.
      digitalWrite(pin_IN1, HIGH);
      digitalWrite(pin_IN2, LOW);
      digitalWrite(pin_IN3, HIGH);
      digitalWrite(pin_IN4, LOW);
    }else if (pos_actualM1 < ref_M1  && pos_actualM2 > ref_M2){ // Se establece el sentido de movimiento para los motores de acuerdo a la referencia.
      digitalWrite(pin_IN1, HIGH);
      digitalWrite(pin_IN2, LOW);
      digitalWrite(pin_IN3, LOW);
      digitalWrite(pin_IN4, HIGH);
    }else if (pos_actualM1 > ref_M1  && pos_actualM2 < ref_M2){ // Se establece el sentido de movimiento para los motores de acuerdo a la referencia.
      digitalWrite(pin_IN1, LOW);
      digitalWrite(pin_IN2, HIGH);
      digitalWrite(pin_IN3, HIGH);
      digitalWrite(pin_IN4, LOW);
    }
    PWM_M1 = constrain(40 + abs(error_M1*KP),0,255); // Se calcula el PWM para el motor 1 y se restringe para valores de 0 a 255.
    PWM_M2 = constrain(80 + abs(error_M2*KP2),0,255); // Se calcula el PWM para el motor 2 y se restringe para valores de 0 a 255.

    if (leer_S1() < ref_M1-3 | leer_S1() > ref_M1+3){ // Si la posición del motor 1 está fuera del rango apropiado....
      digitalWrite(pin_ENA, PWM_M1); // ... lo mueve...
    }else{
      digitalWrite(pin_ENA, 0); // ... o los frena.
    }
    if (leer_S2() < ref_M2-1 | leer_S2() > ref_M2+1){ // Si la posición del motor 2 está fuera del rango apropiado....
      digitalWrite(pin_ENB, PWM_M2); //... lo mueve...
    }else{
      digitalWrite(pin_ENB, 0); // ... o los frena.
    }

    // Bloque de código para monitorear las posiciones, el control y referencia de cada motor.
    pos_actualM1 = leer_S1();
    Serial.print("ANG1: ");
    Serial.print(pos_actualM1);
    Serial.print("\t");
    Serial.print("PWM_M1: ");
    Serial.print(PWM_M1);
    Serial.print("\t");
    Serial.print("REF1: ");
    Serial.println(ref_M1);
    pos_actualM2 = leer_S2();
    Serial.print("ANG2: ");
    Serial.print(pos_actualM2);
    Serial.print("\t");
    Serial.print("PWM_M2: ");
    Serial.print(PWM_M2);
    Serial.print("\t");
    Serial.print("REF2: ");
    Serial.println(ref_M2);
  } while(leer_S1() < ref_M1-3 | leer_S1() > ref_M1+3 | leer_S2() < ref_M2-1 | leer_S2() > ref_M2+1);
  // Todo el ciclo de control se hace mientras las posiciones de los motores estén fuera del rango apropiado.

  digitalWrite(pin_ENA, 0); // Double check para el frenado de ambos motores.
  digitalWrite(pin_ENB, 0);
  Serial.println("******************");
}


// Función para hacer tests.
void llevar2(float ref_M2){
  float pos_actualM2 = leer_S2(); // Obtiene la posición actual del motor 2
  float error_M2; // Calcula el error de posición para el motor 2.
  float KP2 = 10;
  int PWM_M2;
  do{
    error_M2 = ref_M2 - pos_actualM2; // Calcula el error de posición para el motor 1.
    if ( pos_actualM2 > ref_M2){
      digitalWrite(pin_IN3, LOW);
      digitalWrite(pin_IN4, HIGH);
    } else if (pos_actualM2 < ref_M2){
      digitalWrite(pin_IN3, HIGH);
      digitalWrite(pin_IN4, LOW);
    }
    PWM_M2 = constrain(80 + abs(error_M2*KP2),0,255);
    digitalWrite(pin_ENB, PWM_M2);
    pos_actualM2 = leer_S2();
    Serial.print("ANG2: ");
    Serial.print(pos_actualM2);
    Serial.print("\t");
    Serial.print("PWM_M2: ");
    Serial.print(PWM_M2);
    Serial.print("\t");
    Serial.print("REF2: ");
    Serial.println(ref_M2);
  } while(leer_S2() < ref_M2-0.2 | leer_S2() > ref_M2+0.2);
  digitalWrite(pin_ENB, 0);
  Serial.println("******************");
  delay(3000);
}

/**
 * @brief Devuelve el estado del final de carrera con anti-rebote.
 * 
 * @param pin_FC El pin correspondiente al final de carrera.
 * @return Estado del final de carrera
 */
int debounce_FC(int pin_FC){
  int lectura_FC = digitalRead(pin_FC); // Lee el estado actual del final de carrera.
  int count = 0; // Conteo de ciclos para el anti-rebote.
  while(lectura_FC != 0){
    lectura_FC = digitalRead(pin_FC);
    if (lectura_FC == 1){ // Si se presiona el final de carrera se aumenta el conteo...
      count++;
    }
    if (count == 5000){ // ... hasta que llegue al umbral para ser presionado.
      estado_FC2 = 1; // Cambia el estado a "presionado"
      count = 0; // Reinicia el conteo
      return estado_FC2;
      // Serial.print("FC "); 
      // Serial.print(pin_FC);
      // Serial.println(" PRESSED");
    } else {
      estado_FC2 = 0; // Si no se llega al umbral, no cambia el estado a "presionado".
    }
  }
}