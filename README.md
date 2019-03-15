# SoalShift_Modul2_C09

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

    if(((strcmp(pw->pw_name,tname))==0) && ((strcmp(gr->gr_name,tname))==0))
        {
            remove(dpath);
        }



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

## No 5
Kerjakan poin a dan b di bawah:

  a. Buatlah program c untuk mencatat log setiap menit dari file log pada syslog ke /home/[user]/log/[dd:MM:yyyy-hh:mm]/log#.log
  Ket:
  
  -Per 30 menit membuat folder /[dd:MM:yyyy-hh:mm]
  
  -Per menit memasukkan log#.log ke dalam folder tersebut
  
  ‘#’ : increment per menit. Mulai dari 1
  
  b. Buatlah program c untuk menghentikan program di atas.
NB: Dilarang menggunakan crontab dan tidak memakai argumen ketika menjalankan program.

Jawab :
