Import("env")
import os

def dosya_icerigini_oku(dosya_yolu):
    with open(dosya_yolu, "rb") as dosya:
        icerik = dosya.read()
    return icerik

def dosya_icerigini_oku_BaytDizisi(dosya_yolu):
    with open(dosya_yolu, "rb") as dosya:
        icerik = dosya.read()
    return list(icerik)

def byte_dizisini_yaz(byte_dizisi, cikti_dosyasi):
    with open(cikti_dosyasi, "w") as dosya:
        dosya.write("const uint8_t dosya_icerigi[] = {\n    ")
        dosya.write(", ".join(f"0x{b:02X}" for b in byte_dizisi))
        dosya.write("\n};\n")

def modify_and_copy_html_files(src_folder, dest_folder):
    for filename in os.listdir(src_folder):
        if filename.endswith(".html"):
            src_file_path = os.path.join(src_folder, filename)
            dest_file_name_only = os.path.splitext(filename)[0]
            dest_file_name = dest_file_name_only + ".c"
            dest_file_path = os.path.join(dest_folder, dest_file_name)
            
            with open(src_file_path, 'r', encoding='utf-8') as src_file:
                content = src_file.read()
            
            modified_content = "const char " + dest_file_name_only + "[] = R\"rawliteral(\n" + content + "\n)rawliteral";"
            
            with open(dest_file_path, 'w', encoding='utf-8') as dest_file:
                dest_file.write(modified_content)
            

def main():
    env.Replace(PROGNAME="Duplikator_%s" % env.GetProjectOption("program_surumu_yuksek") + "_" + env.GetProjectOption("program_surumu_dusuk"))
    
    for val in os.listdir("../Html Dosyaları"):
        os.

    cikti_dosyasi = "src/file_content.h"  # C++ dosyasının yolu
    byte_dizisi = dosya_icerigini_oku(dosya_yolu)
    byte_dizisini_yaz(byte_dizisi, cikti_dosyasi)

if __name__ == "__main__":
    main()