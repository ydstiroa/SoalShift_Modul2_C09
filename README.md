# SoalShift_Modul2_C09

## Oleh
   * Najatul Muslis Dinantra	05111740000079
   * Yudhistiro Adi Nugroho	05111740000165

### No 1
Elen mempunyai pekerjaan pada studio sebagai fotografer. Suatu hari ada seorang klien yang bernama Kusuma yang meminta untuk mengubah nama file yang memiliki ekstensi .png menjadi “[namafile]_grey.png”. Karena jumlah file yang diberikan Kusuma tidak manusiawi, maka Elen meminta bantuan kalian untuk membuat suatu program C yang dapat mengubah nama secara otomatis dan diletakkan pada direktori /home/[user]/modul2/gambar.
Catatan : Tidak boleh menggunakan crontab.

Jawab :

Pertama buka directory yang mengandung file .png dengan menggunakan 

    DIR *d;
    
    struct dirent *dir;
    d = opendir("/home/yudhis/Documents/");

    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            
        }
        closedir(d);
    }

Setelah itu untuk mengetahui bagaimana caranya mencari semua yang mempuinya ekstensi .png adalah dengan cara menghitung panjang stringnya dan membacanya dari belakang lalu di compare jika sama dengan .jpg maka akan di ambil dan di concat dengan string yang mengandung directory tujuan. concat kembali hasil sebelumnya dengan string "_ grey.png". untuk menghapus file dengan ekstensi .png juga dilakukan dengan membaca panjang stringnya dari belakang dan dibuat kosong dengan "\0". hasil yabg sudah di concat dan di ubah dengan namanya di move ke folder yang dituju. (Gunakan daemon untuk automasinya)

     char namaFile[500];
          int len = (int) strlen(dir->d_name);
          char *name = dir->d_name;
          if(name[len-1] == 'g' && name[len-2] == 'n' && name[len-3] == 'p' && name[len-4] == '.'){
                  printf("%s %d\n", dir->d_name, (int) strlen(dir->d_name));
        strcpy(namaFile, "/home/yudhis/Documents/modul2/gambar/");
        strcat(namaFile, name);
        len = (int)strlen(namaFile);
        namaFile[len-4] = '\0'; //delete file
        strcat(namaFile, "_grey.png");
        if(fork()==0){
        char *argv[] = {"mv", name, namaFile, NULL};
        execv("/bin/mv", argv);
        }
        printf("%s\n", namaFile);
          }
          
Code lengkapnya : [Soal 1](/s1.c)

## No 2
Pada suatu hari Kusuma dicampakkan oleh Elen karena Elen dimenangkan oleh orang lain. Semua kenangan tentang Elen berada pada file bernama “elen.ku” pada direktori “hatiku”. Karena sedih berkepanjangan, tugas kalian sebagai teman Kusuma adalah membantunya untuk menghapus semua kenangan tentang Elen dengan membuat program C yang bisa mendeteksi owner dan group dan menghapus file “elen.ku” setiap 3 detik dengan syarat ketika owner dan grupnya menjadi “www-data”. Ternyata kamu memiliki kendala karena permission pada file “elen.ku”. Jadi, ubahlah permissionnya menjadi 777. Setelah kenangan tentang Elen terhapus, maka Kusuma bisa move on.
Catatan: Tidak boleh menggunakan crontab

Jawab :

Pertama inisialisasi variable struct stat perlu diketahui bahwa struct stat digunakan untuk mengambil nilai st_uid (User id ), dan st_gid (Group id)
    
    struct stat ls;


Masukkan tujuan directory ke dalam char dan juga masukkan "www-data" kedalam char 

    char dpath[50]="/home/yudhis/Documents/hatiku/elen.ku";
    char tname[20]="www-data";
    
Gunakan stat untuk mendapatkan informasi
    
    stat(dpath, &ls);
    
dapatkan user id dengan getpwuid() dan group id dengan dengan getgrgid()
    
    struct passwd *pw = getpwuid(ls.st_uid);
    struct group  *gr = getgrgid(ls.st_gid);
    
untuk melihat apakah file sudah memiliki user id dan group id = www-data maka harus di compare terlebih dahulu dan jika benar maka file akan dihapus

    if(((strcmp(pw->pw_name,tname))==0)){
        if(((strcmp(gr->gr_name,tname))==0))
            {
                remove(dpath);
            }
        }

Code lengkapnya : [Soal 2](/s22.c)

## No 3
Diberikan file campur2.zip. Di dalam file tersebut terdapat folder “campur2”. 
Buatlah program C yang dapat :
i)  mengekstrak file zip tersebut.
ii) menyimpan daftar file dari folder “campur2” yang memiliki ekstensi .txt ke dalam file daftar.txt. 
Catatan:  
Gunakan fork dan exec.
Gunakan minimal 3 proses yang diakhiri dengan exec.
Gunakan pipe
Pastikan file daftar.txt dapat diakses dari text editor

Jawab :

## No 4
Dalam direktori /home/[user]/Documents/makanan terdapat file makan_enak.txt yang berisikan daftar makanan terkenal di Surabaya. Elen sedang melakukan diet dan seringkali tergiur untuk membaca isi makan_enak.txt karena ngidam makanan enak. Sebagai teman yang baik, Anda membantu Elen dengan membuat program C yang berjalan setiap 5 detik untuk memeriksa apakah file makan_enak.txt pernah dibuka setidaknya 30 detik yang lalu (rentang 0 - 30 detik).
Jika file itu pernah dibuka, program Anda akan membuat 1 file makan_sehat#.txt di direktori /home/[user]/Documents/makanan dengan '#' berisi bilangan bulat dari 1 sampai tak hingga untuk mengingatkan Elen agar berdiet.

Contoh:
File makan_enak.txt terakhir dibuka pada detik ke-1
Pada detik ke-10 terdapat file makan_sehat1.txt dan makan_sehat2.txt

Catatan: 
dilarang menggunakan crontab
Contoh nama file : makan_sehat1.txt, makan_sehat2.txt, dst

Jawab :

Pertama inisialisasi variable struct stat perlu diketahui bahwa struct stat digunakan untuk mengambil nilai

    struct stat file_status;
    stat("/home/najaslanardo/Documents/makanan/makan_enak.txt",&file_status);
    
cek apakah file pernah dibuka setidaknya dalam 30 detik. lalu buat variable char yang berisi tujuan dan buat juga variable char baru untuk menampung increment dimana di inisialisasi = 1 dan concat kedua char tersebut. setelah itu open file yang sudah di concat read lalu lakukan write didalam file tersebut. jika sudah close file

	if(file_status.st_atime + 30 > time(NULL)){int ingatdiet =1;
      while(1){
        char tempstr[50]= "";
        char newfile[350] = "/home/najaslanardo/Documents/makanan/makan_sehat";
        sprintf(tempstr,"%d.txt",ingatdiet);strcat(newfile, tempstr);
        FILE *temp = fopen(newfile, "r");
        if(!temp){
          FILE *temp1 = fopen(newfile,"w");
          fclose(temp1);break;
        }
        fclose(temp);
        ingatdiet++;
      }
    }

Code lengkapnya : [Soal 4](/s4.c)

## No 5
Kerjakan poin a dan b di bawah:

a.Buatlah program c untuk mencatat log setiap menit dari file log pada syslog ke /home/[user]/log/[dd:MM:yyyy-hh:mm]/log#.log
  Ket:
  
   -Per 30 menit membuat folder /[dd:MM:yyyy-hh:mm]
  
   -Per menit memasukkan log#.log ke dalam folder tersebut
  
   ‘#’ : increment per menit. Mulai dari 1
  
b.Buatlah program c untuk menghentikan program di atas.
NB: Dilarang menggunakan crontab dan tidak memakai argumen ketika menjalankan program.

Jawab :

a. Pertama-tama cari tahu bagaimana caranya mendapatkan current time maka digunakan 

    #include <time.h>

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    printf("now: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    
setelah itu masukkan current date kedalam sebuah variable yang akan terus diupdate setelah 30 menit

    if(i%1800==0){
        sprintf(waktu,"%d-%d-%d-%d:%d",tm.tm_mday,tm.tm_mon + 1,tm.tm_year + 1900,tm.tm_hour, tm.tm_min);
        printf("%s\n",waktu);
        }

Buat folder dengan format current date agar saat di exec program tidak berhenti maka harus memanggil fungsi fork()

    child = fork();
	if(child==0){
		char *argv[] = {"mkdir", waktu, NULL};
		execv("/bin/mkdir", argv);
	}
    
Buat file yang diarahkan pada folder yang telah dibuat sebelumnya dengan format nama "log#.log" dimana tiap menit file tersebut akan terus bertambah dan jangan lupa untuk mencatat lognya dari /var/log/syslog . 

    if(child==0){
        sprintf(data,"log%d.log",i);
        strcat(dpath,data);
        char *argv[] = {"cp", "/var/log/syslog",dpath, NULL};
            execv("/bin/cp", argv);
        }

Hal yang penting selanjutnya adalah menentukan path destinationnya (diperlukan untuk membuat file nantinya) gunakan concat berikut adalah potongan alur concat

    char dpath[100]= "/home/yudhis/Documents/";
    sprintf(waktu,"%d-%d-%d-%d:%d",tm.tm_mday,tm.tm_mon + 1,tm.tm_year + 1900,tm.tm_hour, tm.tm_min);
    strcat(dpath,waktu);
    strcat(dpath,data);
	strcat(dpath,"/");
	
untuk melanjutkan ke soal b maka harus didapatkan terlebih dahulu pid dari program yang dijalankan dengan membuka directorynya dan menuliskan nomor pidnya dan disimpan kedalam sebuah file dengan ekstensi .txt (disini diberi nama "gpid.txt")

	FILE * gpid;
		gpid = fopen ("/home/yudhis/Documents/gpid.txt", "w+");
		fprintf(gpid, "%d",getpid());
		fclose(gpid);
    
Code lengkapnya : [Soal 5a](/s5.c)

b. Untuk menghentikan program yang dijalankan pada sebelumnya maka kita harus membuka file yang telah dibuat pada program sebelumnya berupa "gpid.txt" lalu dimasukkan kedalam sebuah variable. setelah itu yang harus dilakukan adalah kill angka pid yang didapat dengan menjalankan fungsi kill, lalu jika sudah di kill maka file tersebut di remove.

	  pid_t npid;
		FILE * gpid;

		gpid = fopen ("gpid.txt", "r");
		fscanf(gpid, "%d", &npid);
		kill(npid,SIGKILL);
		remove("npid.txt");
		fclose(gpid);

Code lengkapnya : [Soal 5b](/pkill.c)
