#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <time.h>

#define HTML_FILE "index.html"
#define BUFFER_SIZE 4096

void read_proc_file(const char *path, char *buffer, size_t size) {
    FILE *file = fopen(path, "r");
    if (!file) return;
    fgets(buffer, size, file);
    fclose(file);
}

int main() {
    char buffer[BUFFER_SIZE];
    FILE *html = fopen(HTML_FILE, "w");
    if (!html) return 1;

    fprintf(html, "<html><head><meta http-equiv='refresh' content='5'></head><body>");
    fprintf(html, "<h1>Informações do Sistema</h1>");

    time_t now = time(NULL);
    fprintf(html, "<p>Data e Hora: %s</p>", ctime(&now));

    read_proc_file("/proc/version", buffer, sizeof(buffer));
    fprintf(html, "<p>Versão do Sistema: %s</p>", buffer);

    read_proc_file("/proc/uptime", buffer, sizeof(buffer));
    fprintf(html, "<p>Uptime: %s</p>", buffer);

    read_proc_file("/proc/cpuinfo", buffer, sizeof(buffer));
    fprintf(html, "<p>CPU Info: %s</p>", buffer);

    read_proc_file("/proc/meminfo", buffer, sizeof(buffer));
    fprintf(html, "<p>Memória RAM: %s</p>", buffer);

    fprintf(html, "<h2>Processos em execução</h2><ul>");
    DIR *dir = opendir("/proc");
    struct dirent *entry;
    while ((entry = readdir(dir))) {
        if (atoi(entry->d_name) > 0) {
            snprintf(buffer, sizeof(buffer), "/proc/%s/comm", entry->d_name);
            read_proc_file(buffer, buffer, sizeof(buffer));
            fprintf(html, "<li>PID: %s - %s</li>", entry->d_name, buffer);
        }
    }
    closedir(dir);
    fprintf(html, "</ul></body></html>");
    
    fclose(html);
    return 0;
}