# soal-shift-sisop-modul-2-D11-2021
Modul 2 - Daemon dan Proses 
|Nama|NRP|
|----|-----|
|Afifah Nur Sabrina Syamsudin|05111940000022|
|Dewi Mardani Cristin|05111940000225|
|Avind Pramana Azhari|05111940000226|
## Soal No 2
Loba bekerja di sebuah petshop terkenal, suatu saat dia mendapatkan zip yang berisi banyak sekali foto peliharaan dan Ia diperintahkan untuk mengkategorikan foto-foto peliharaan tersebut. Loba merasa kesusahan melakukan pekerjaanya secara manual, apalagi ada kemungkinan ia akan diperintahkan untuk melakukan hal yang sama. Kamu adalah teman baik Loba dan Ia meminta bantuanmu untuk membantu pekerjaannya.

Pertama-tama program perlu mengextract zip yang diberikan ke dalam folder “/home/[user]/modul2/petshop”. Karena bos Loba teledor, dalam zip tersebut bisa berisi folder-folder yang tidak penting, maka program harus bisa membedakan file dan folder sehingga dapat memproses file yang seharusnya dikerjakan dan menghapus folder-folder yang tidak dibutuhkan.
Foto peliharaan perlu dikategorikan sesuai jenis peliharaan, maka kamu harus membuat folder untuk setiap jenis peliharaan yang ada dalam zip. Karena kamu tidak mungkin memeriksa satu-persatu, maka program harus membuatkan folder-folder yang dibutuhkan sesuai dengan isi zip.
Contoh: Jenis peliharaan kucing akan disimpan dalam “/petshop/cat”, jenis peliharaan kura-kura akan disimpan dalam “/petshop/turtle”.
Setelah folder kategori berhasil dibuat, programmu akan memindahkan foto ke folder dengan kategori yang sesuai dan di rename dengan nama peliharaan.
Contoh: “/petshop/cat/joni.jpg”. 
Karena dalam satu foto bisa terdapat lebih dari satu peliharaan maka foto harus di pindah ke masing-masing kategori yang sesuai. Contoh: foto dengan nama “dog;baro;1_cat;joni;2.jpg” dipindah ke folder “/petshop/cat/joni.jpg” dan “/petshop/dog/baro.jpg”.
Di setiap folder buatlah sebuah file "keterangan.txt" yang berisi nama dan umur semua peliharaan dalam folder tersebut. Format harus sesuai contoh.

### a: Jawaban dan Penjelasan
Pertama-tama program perlu mengextract zip yang diberikan ke dalam folder “/home/[user]/modul2/petshop”. Karena bos Loba teledor, dalam zip tersebut bisa berisi folder-folder yang tidak penting, maka program harus bisa membedakan file dan folder sehingga dapat memproses file yang seharusnya dikerjakan dan menghapus folder-folder yang tidak dibutuhkan.
```
int main()
{
    char path[100];

        id_t child_id;
        int status=0;

        child_id = fork();

        if (child_id < 0) {
            exit(EXIT_FAILURE); 
        }
	
        if (child_id == 0) {
            char *argv[] = {"unzip", "/home/dewi/modul2/pets.zip", "*.jpg", "-d", "/home/dewi/modul2/petshop", NULL};
            execv("/usr/bin/unzip", argv);
        } else {
            while(wait(&status) > 0);
            checkFiles("/home/dewi/modul2/petshop");
        }
    return 0;
}
```
Jadi berdasarkan syntax diatas untuk memngekstrak zip dan menghapus folder yang tidak  penting kita dapat menggunakan syntax 
```char *argv[] = {"unzip", "/home/dewi/modul2/pets.zip", "*.jpg", "-d", "/home/dewi/modul2/petshop", NULL};```
- ```-unzip``` = Untuk penamaan perintah
- ``` "/home/dewi/modul2/pets.zip"``` = tempat dimana file yang akan diekstrak berada
- ``` "*.jpg"``` = Untuk mengunzip file yang hanya bertipe jpg
- ```-d``` = Untuk menunjuk ke directory mana file akan di unzip
- ```"/home/dewi/modul2/petshop"``` = sebagai tempat peleteakkan file zip yang tealh di ekstrak
kemudian syntax tersebut kita eksekusi dengan perintah sebagai berikut
```execv("/usr/bin/unzip", argv);```
B. Foto peliharaan perlu dikategorikan sesuai jenis peliharaan, maka kamu harus membuat folder untuk setiap jenis peliharaan yang ada dalam zip. Karena kamu tidak mungkin memeriksa satu-persatu, maka program harus membuatkan folder-folder yang dibutuhkan sesuai dengan isi zip. Contoh: Jenis peliharaan kucing akan disimpan dalam /petshop/cat, jenis peliharaan kura-kura akan disimpan dalam /petshop/turtle.

Pertama pada fungsi ini kita akan mengujungi file-file di dalam driectory secara rekursif dan didalam fungsi rekursi ini kita akan memanggil fungsi createFolder untuk membuat folder berdasarkan jenis peliharaan.
```
void checkFiles(char *basePath)
{
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);
    char *token;

    if (!dir)
        return;

    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            char nama[656];
            char *str;
            str = dp->d_name;
           
            snprintf(nama, sizeof nama, "%s", dp->d_name);
            token  = strtok(nama, ";_");

            
            char kind[1600], name[1600], age[1600];
            char *info[2][3];
            int banyak=0;
            while(token != NULL){
                int data = 0;
                while(data<3){
                    info[banyak][data] = token;
                    token = strtok(NULL, ";_");
                    data++;
                }
                banyak++;
            }
            char *usia;
            for (int i = 0; i < banyak; i++) {
                createFolder(info[i][0]);
                copyFiles(info[i][0], info[i][1], str);
                createKeterangan(info[i][0], info[i][1], info[i][2], i, banyak);
            }
            deleteFiles(str);
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);

            checkFiles(path);
        }
    }

    closedir(dir);
}
```
Pada fungsi ini kita akan membuat folder di dalam folder petshop berdasarkan jenis peliharaan
```
void createFolder(char *nameFolder){
    int status = 0;
    if(fork()==0){
        char buf1[256];
        snprintf(buf1, sizeof buf1, "petshop/%s", nameFolder);
        char *argv[] = {"mkdir", "-p", buf1, NULL};
        execv("/bin/mkdir", argv);
    }
    while(wait(&status)>0);
}
```
Pada saat proses sedang berlangsung kita akan membuat folder baru pertama kita deklarasikan terlebih dahulu suatu variabel buf1 yang akan menampung penamaan folder ```snprintf``` berguna untuk mempassing suatu string ke dalam suatu variabel jadi pada case ini nama foler akan di passing ke variabel buf1. Kemudian untuk membuat directory kita dapat mendeklarasikan string argc yang berisi perintah mkdir. ```-p``` untuk membuat parent directory karena dalam file terdapat banayak jenis peliharaan yang sama jadi ktia mengunakan ```-p``` agar saat jenis peliharaan terdapat lebih dari 1 maka akan membuat 1 folder saja.Kemudian kita eksekusi perogram tadi menggunakan perintah   ```execv("/bin/mkdir", argv);```

c. Setelah folder kategori berhasil dibuat, programmu akan memindahkan foto ke folder dengan kategori yang sesuai dan di rename dengan nama peliharaan. Contoh: /petshop/cat/joni.jpg.
d. Karena dalam satu foto bisa terdapat lebih dari satu peliharaan maka foto harus di pindah ke masing-masing kategori yang sesuai. Contoh: foto dengan nama dog;baro;1_cat;joni;2.jpg dipindah ke folder /petshop/cat/joni.jpg” dan “/petshop/dog/baro.jpg.
```
void copyFiles(char *namaFolder, char *nama, char *namaFile){
    char buf1[256];
    char buf2[256];
    snprintf(buf1, sizeof buf1, "petshop/%s", namaFile);
    snprintf(buf2, sizeof buf2, "petshop/%s/%s.jpg", namaFolder, nama);
    printf("%s\n", buf1);
    printf("%s\n", buf2);
    if(fork()==0){
        char *argv[] = {"cp", buf1, buf2, NULL};
        execv("/bin/cp", argv);
    }
    while(wait(&status)>0);
}
```
Untuk memindahkan foto ke folder kita dengan nama yang sesuai kita dapat mengcopy file foto lalu menghapus file foto yang masih ada di directory petshop. Seperti syntax yang ada diatas pertama kita deklarasikan varaibel ```buf1``` dan ```buf2``` kemudian kita tampung nama file kedalam variable buf1 dan namafolder dan nama hewan akan kita tampung ke dalam variabel buf2. Kemudiaan ketika proses berjalan kita dapat mengcopy file ``` char *argv[] = {"cp", buf1, buf2, NULL};``` kemudian program dapat dieksekusi.

e. Di setiap folder buatlah sebuah file keterangan.txt yang berisi nama dan umur semua peliharaan dalam folder tersebut. Format harus sesuai contoh.
```
void createKeterangan(char *folder, char *namaHewan, char *umurHewan, int pembantu, int banyak){
    char *umur;
    int status = 0;
    umur = strtok(umurHewan, ".jpg");
    char umurReal[100];
    strcpy(umurReal, umur);
    // printf("umurReal = %s\n", umurReal);
    if(strcmp(umurReal, "0") == 0){
        umur = "0.5";
    }
    char buf1[10000];
    snprintf(buf1, sizeof buf1, "petshop/%s/keterangan.txt", folder);
    printf("%s\n", buf1);
    FILE *keterangan;
    keterangan = fopen(buf1, "a+");
    fprintf(keterangan, "nama : %s", namaHewan);
    fprintf(keterangan, "\n");
    fprintf(keterangan, "umur : %s tahun", umur);
    fprintf(keterangan, "\n\n");
    fclose(keterangan);
}
```
Untuk membuat keterangan disetiap file kita dapat menggunakan fopen untuk membuka file dan ```-a``` untuk membuka file sesuai nama filenya untuk ditambahkan datanya dipaling bawah baris terakhir dan apabila tidak ada maka akan otomatis menambahkan file baru. Kemudian kita dapat mencetaknya nama dan umur menggunakan fprint dan setelah selesai kita harus menutup file dengan menggunakan ```fclose```.
## Output
![output1](https://user-images.githubusercontent.com/80894892/115991895-4ea9ec80-a5fd-11eb-91f7-e05e4dd341ac.png)

![output2](https://user-images.githubusercontent.com/80894892/115991898-51a4dd00-a5fd-11eb-90ff-bf63d5381a70.png)

![output3](https://user-images.githubusercontent.com/80894892/115991899-549fcd80-a5fd-11eb-8df7-3e80173a56e7.png)

![output4](https://user-images.githubusercontent.com/80894892/115991901-56699100-a5fd-11eb-9dd4-8ada2bf05c7f.png)

## Soal No 3
Ranora adalah mahasiswa Teknik Informatika yang saat ini sedang menjalani magang di perusahan ternama yang bernama “FakeKos Corp.”, perusahaan yang bergerak dibidang keamanan data. Karena Ranora masih magang, maka beban tugasnya tidak sebesar beban tugas pekerja tetap perusahaan. Di hari pertama Ranora bekerja, pembimbing magang Ranora memberi tugas pertamanya untuk membuat sebuah program. 

(a) Membuat sebuah program C yang dimana setiap 40 detik membuat sebuah direktori dengan nama sesuai timestamp **[YYYY-mm-dd_HH:ii:ss]**.

(b) Tiap-tiap folder lalu diisi dengan 10 gambar yang di download dari
**https://picsum.photos/**, dimana tiap gambar di download setiap 5 detik. Tiap
gambar berbentuk persegi dengan ukuran _**(t%1000)+50**_ piksel dimana t adalah
detik Epoch Unix. Gambar tersebut diberi nama dengan format timestamp **[YYYY-
mm-dd_HH:ii:ss]**.

(c) Setelah direktori telah terisi dengan 10 gambar, program tersebut akan membuat sebuah file **“status.txt”**,
dimana didalamnya berisi pesan **“Download Success”** yang terenkripsi dengan teknik Caesar Cipher dan dengan shift 5.
Caesar Cipher adalah Teknik enkripsi sederhana yang dimana dapat melakukan enkripsi string sesuai dengan shift/key yang kita tentukan.
Misal huruf “A” akan dienkripsi dengan shift 4 maka akan menjadi “E”. Karena Ranora orangnya perfeksionis dan rapi,
dia ingin setelah file tersebut dibuat, direktori akan di zip dan direktori akan didelete, sehingga menyisakan hanya file zip saja.

(d) Untuk mempermudah pengendalian program, pembimbing magang Ranora ingin program tersebut akan men-generate sebuah program “Killer” yang executable,
dimana program tersebut akan menterminasi semua proses program yang sedang berjalan dan akan menghapus dirinya sendiri setelah program dijalankan.
Karena Ranora menyukai sesuatu hal yang baru, maka Ranora memiliki ide untuk program “Killer” yang dibuat nantinya harus merupakan **program bash**.

(e) Pembimbing magang Ranora juga ingin nantinya program utama yang dibuat Ranora dapat dijalankan di dalam dua mode.
Untuk mengaktifkan mode pertama, program harus dijalankan dengan argumen -z, dan Ketika dijalankan dalam mode pertama,
program utama akan langsung menghentikan semua operasinya Ketika program Killer dijalankan.
Sedangkan untuk mengaktifkan mode kedua, program harus dijalankan dengan argumen -x, dan Ketika dijalankan dalam mode kedua, program utama akan berhenti namun membiarkan proses
di setiap direktori yang masih berjalan hingga selesai
(Direktori yang sudah dibuat akan mendownload gambar sampai selesai dan membuat file txt, lalu zip dan delete direktori).

Ranora meminta bantuanmu untuk membantunya dalam membuat program tersebut. Karena kamu anak baik dan rajin menabung,
bantulah Ranora dalam membuat program tersebut!
Note:
- Tidak boleh menggunakan system() dan mkdir()
- Program utama merupakan **SEBUAH PROGRAM C**
- Wajib memuat algoritma Caesar Cipher pada program utama yang dibuat

### a: Jawaban dan Penjelasan
Pada soal bagian a kita diminta untuk Membuat sebuah program C yang dimana setiap 40 detik membuat sebuah direktori dengan nama sesuai timestamp **[YYYY-mm-dd_HH:ii:ss]**.
```
 while(1){
        
        char currenttime[100];
        time_t n = time(NULL);
        struct tm* t = localtime(&n);
        strftime(currenttime, 40, "%Y-%m-%d_%H:%M:%S", t);

        pid_t child;
        child = fork();

        if(child < 0){
            exit(0);
        }

        if(child == 0){
            char *argv[] = {"mkdir", currenttime, NULL};
            execv("/bin/mkdir", argv);
        }
        sleep(40);
```
berdasarkan syntax diatas
- ```time_t```: memanipulasi waktu
- ```localtime```: menyimpan waktu lokal (yang ada pada komputer)
- ```strftime```:  atur format waktu dan disimpan di string  *_currenttime_*
- ```mkdir```: membuat direktori atau folder
- ```sleep(30)```: interval waktu 40 detik tiap directory

Output:

![Gambar output bagian a](https://github.com/sisopd11/soal-shift-sisop-modul-2-D11-2021/blob/main/soal3/Screenshot%20from%202021-04-23%2020-48-44.png)

### b: Jawaban dan Penjelasan
Pada soal bagian b kita diminta untuk download 10 gambar dari
**https://picsum.photos/**, dimana tiap gambar di download setiap 5 detik. Tiap
gambar berbentuk persegi dengan ukuran _**(t%1000)+50**_ piksel dimana t adalah
detik Epoch Unix. Gambar tersebut diberi nama dengan format timestamp **[YYYY-
mm-dd_HH:ii:ss]**.
```
chdir(currenttime);
    	    int i;

            for(i = 0; i < 10; i++){
                char currenttime2[100];
                time_t n2 = time(NULL);
                struct tm* t2 = localtime(&n2);
                strftime(currenttime2, 40, "%Y-%m-%d_%H:%M:%S", t2);

                char link[100];
                sprintf(link, "https://picsum.photos/%ld", (n2 % 1000) + 100);

                pid_t child3;
                child3 = fork();

                if(child3 < 0){
                    exit(0);
                }

                if(child3 == 0){
                    char *argv[] = {"wget", link, "-O", currenttime2, "-o", "/dev/null", NULL}; 
                    execv("/usr/bin/wget", argv);
                }
                sleep(5);
```
berdasarkan syntax diatas:
-  ```chdir```: arah direktori kembali ke *_currenttime_*
- perulangan ```for```: agar dapat mengunduh 10 gambar
- ```strftime```:  atur format waktu dan disimpan di string *_currenttime2_*
- ```sprintf```: mengisi string *_link_* dengan format *_(now2 % 1000) + 50_*
- ```wget```: program mendowload sesuai dengan format waktu tiap mendownload gambar
- 
Output:
![Gambar output bagian b](https://github.com/sisopd11/soal-shift-sisop-modul-2-D11-2021/blob/main/soal3/Screenshot%20from%202021-04-23%2020-50-31.png)

### c: Jawaban dan Penjelasan
Pada soal bagian c diminta untuk membuat file "Status.txt" yang isinya tulisan "Download Success" setelah directoy terisi 10 gambar.
Setelah itu directory dizip dan dihapus agar terlihat lebih rapih.
```
int status2;
            while(wait(&status2) > 0);
	    
            chdir("..");
            char currenttime3[50];
            strcpy(currenttime3, currenttime);
            strcat(currenttime3, ".zip");

            pid_t child4;
            child4 = fork();
            
            if(child4 < 0){
                exit(0);
            }

            if(child4 == 0){
                char *argv[] = {"zip", "-r", currenttime3, currenttime, NULL};
                execv("/usr/bin/zip", argv);
            }

            int status3;
            while(wait(&status3) > 0);

            pid_t child5;
            child5 = fork();

	        if(child5 < 0){
                exit(0);
            }

            if(child5 == 0){
                char *argv[] = {"rm", "-r", currenttime, NULL};
            	execv("/bin/rm", argv);
            }
```
Caesar Chiper
```
void encrypt(char arr[]){
      char status[40] = "Download Success";
      
      int i;
      for(i = 0; i < strlen(arr); i++){
            arr[i] = arr[i] - 10;
      }
      printf("%s\n", status);
}
```
Berdasarkan syntax diatas
- ```chdir```: kembali ke folder parentKita mengubah direktori ke folder parent awal
- ```strcpy```: mencopy nama folder *_currenttime_*
- ```strcat```: membuat nama *_.zip_* di *_currenttime3_*.
- ```zip```: menzip dengan nama *_currenttime3_*
- ```rm -r```: hapus folder yang telah dizip berdasarkan dari *_currenttime_*.

Output:
![Gambar output bagian c](https://github.com/sisopd11/soal-shift-sisop-modul-2-D11-2021/blob/main/soal3/Screenshot%20from%202021-04-23%2020-49-00.png)

### d: Jawaban dan Penjelasan
Pada soal bagian d diminta untuk membuat file "Killer.sh" untuk memudahkan ranora dalam mengontrol program, menterminate dan menghapus programnya sendiri saat program berjalan
```
int status;
    FILE* kill;
    
    kill = fopen("killer.sh", "w");
    fprintf(kill, "#!/bin/bash\nkill %d\nkill %d\necho \'Killed program.\'\nrm \"$0\"", getpid() + 2, getpid() + 3);
    fclose(kill);
    
    pid_t child;
    child = fork();
    
    if(child < 0){
        exit(0);
    }

    if(child = 0){
        char *argv[] = {"chmod", "u+x", "killer.sh", NULL};
        execv("/bin/chmod", argv);
    }

    while(wait(&status) > 0);
```
berdasarkan syntax diatas:
- ```fopen```: create file *_killer.sh_*, di isi dengan bash untuk membunuh program.
- ```fprintf```: perintah untuk membunuh program
- ```chmod u+x```: akses file ke user untuk mengeksekusi killer.sh. 

Output:
![Gambar output bagian d](https://github.com/sisopd11/soal-shift-sisop-modul-2-D11-2021/blob/main/soal3/Screenshot%20from%202021-04-23%2020-51-48.png)

### e: Jawaban dan Penjelasan
Pada soal bagian e diminta untuk membuat program dapat berjalan dengan dua mode "-x": program berhenti saat semua proses selesai dan "-z": langsung menghentikan program.
```
int main(int argc, char* argv[]){

    if(argc != 2 || (argv[1][1] != 'x' && argv[1][1] != 'z')){ 
        
        printf("Invalid argumen, Input -x  or -z\n");
        exit(0);
    }
    
...
if(argv[1][1] == 'a') prctl(PR_SET_PDEATHSIG, SIGHUP);
```
berdasarkan syntax diatas:
- Check jika argumen char ```argc``` tidak sama dengan 2 atau inputan argumen yang bukan di passing ```argv``` sama dengan x dan z,
muncul tulisan *_Invalid argumen, Input -x  or -z_*
- ```prctl``` sebagai system call linux
- ```PR_SET_PDEATHSIG``` dan ```SIGHUP```: menge*_set_* signal death dan memberhentikan program.

Output:
![Gambar output bagian e](https://github.com/sisopd11/soal-shift-sisop-modul-2-D11-2021/blob/main/soal3/Screenshot%20from%202021-04-23%2021-49-32.png)
![Gambar output bagian e](https://github.com/sisopd11/soal-shift-sisop-modul-2-D11-2021/blob/main/soal3/Screenshot%20from%202021-04-23%2021-50-09.png)

## Kendala yang dihadapi
1. Belum bisa membuat file status.txt
2. Program killer kadang berjalan kadang tidak
3. Saat membuat folder baru, tidak pada folder soal3 melainkan didalam folder yang sudah selesai mendownload 10 gambar begitu seterusnya
4. Ada folder kosong saat membuat folder baru setiap membuat folder baru begitu seterusnya
