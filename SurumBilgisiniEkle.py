Import("env")
import os

def modify_and_copy_html_files(src_folder, dest_folder_src, dest_folder_inc):
    for filename in os.listdir(src_folder):
        if filename.endswith(".html"):
            src_file_path = os.path.join(src_folder, filename)
            dest_file_name_only = os.path.splitext(filename)[0]
            dest_file_path_src = os.path.join(dest_folder_src, dest_file_name_only + ".cpp")
            dest_file_path_inc = os.path.join(dest_folder_inc, dest_file_name_only + ".h")

            with open(src_file_path, 'r', encoding='utf-8') as src_file:
                content = src_file.read()
            
            modified_content = "#include \"" + dest_file_name_only + ".h\"\n\nconst char " + dest_file_name_only + "[] = R\"rawliteral(\n" + content + ")rawliteral\";"
            
            with open(dest_file_path_src, 'w', encoding='utf-8') as dest_file:
                dest_file.write(modified_content)
            
            h_dosyasi_icerigi = "#ifndef __" + dest_file_name_only + "__H__\n#define __" + dest_file_name_only + "__H__\n\nextern const char " + dest_file_name_only + "[];\n\n#endif"

            with open(dest_file_path_inc, 'w', encoding='utf-8') as dest_file:
                dest_file.write(h_dosyasi_icerigi)

env.Replace(PROGNAME="Duplikator_%s" % env.GetProjectOption("program_surumu_yuksek") + "_" + env.GetProjectOption("program_surumu_dusuk"))
modify_and_copy_html_files("../Html_Dosyalari/", "src/", "include/")