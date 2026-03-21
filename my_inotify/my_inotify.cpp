#include <iostream>
#include <ostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/inotify.h>
#include <unistd.h>
#include <vector>

#define MAX_EVENTS                                                             \
  1024 /*Максимальное кличество событий для обработки за один раз*/
#define LEN_NAME                                                               \
  16 /*Будем считать, что длина имени файла не превышает 16 символов*/
#define EVENT_SIZE (sizeof(struct inotify_event)) /*размер структуры события*/
#define BUF_LEN                                                                \
  (MAX_EVENTS *                                                                \
   (EVENT_SIZE + LEN_NAME)) /*буфер для хранения данных о событиях*/

using namespace std;

int main(int argc, char *argv[]) {
  vector<string> buffer_with_agrs;
  for (int i = 1; i < argc; ++i) {
    if (string(argv[i]) != "--monitor")
      buffer_with_agrs.push_back(argv[i]);

    cout << argv[i] << endl;
  }
  // if in buffer first element != --monitor do somple logic , else do monitor
  // logic logic
  int length, i = 0, wd;
  int fd;
  char buffer[BUF_LEN];

  /* Init Inotify*/

  fd = inotify_init1(0);
  if (fd < 0) {
    perror("Couldn't initialize inotify");
  }
  for (string element : buffer_with_agrs) {
    wd = inotify_add_watch(fd, element.c_str(),
                           IN_CLOSE | IN_MODIFY | IN_CREATE | IN_DELETE);
    if (wd == -1) {
      printf("Couldn't add watch to %s\n", element.c_str());
    } else {
      printf("Watching:: %s\n", element.c_str());
    }
  }

  if (string(argv[1]) != "--monitor") {

    cout << "CLASSIC MODE:" << endl;

    i = 0;
    /* высчитываем размер файлового дескриптора*/
    length = read(fd, buffer, BUF_LEN);
    if (length < 0) {
      perror("read");
    }
    struct inotify_event *event = (struct inotify_event *)&buffer[i];
    if (event->len) {
      if (event->mask & IN_CLOSE) {
        if (event->mask & IN_ISDIR)
          printf("DIRECTORY CLOSED: %s \n", event->name);
        else
          printf("FILE CLOSED %s \n", event->name);
      }
      if (event->mask & IN_MODIFY) {
        if (event->mask & IN_ISDIR)
          printf("DIRECTORY MODIFIED: %s \n", event->name);
        else
          printf("FILE MODIFIED %s \n", event->name);
      }
      if (event->mask & IN_CREATE) {
        if (event->mask & IN_ISDIR)
          printf("DIRECTORY CREATED: %s \n", event->name);
        else
          printf("FILE CREATED %s \n", event->name);
      }
      if (event->mask & IN_DELETE) {
        if (event->mask & IN_ISDIR)
          printf("DIRECTORY DELETED: %s \n", event->name);
        else
          printf("FILE DELETED %s \n", event->name);
      }
    }

    inotify_rm_watch(fd, wd);
    close(fd);

  } else {
    cout << "MINOTOR MODE:" << endl;

    while (1) {
      i = 0;
      /* высчитываем размер файлового дескриптора*/
      length = read(fd, buffer, BUF_LEN);
      if (length < 0) {
        perror("read");
      }

      while (i < length) {
        struct inotify_event *event = (struct inotify_event *)&buffer[i];
        if (event->len) {
          if (event->mask & IN_CLOSE) {
            if (event->mask & IN_ISDIR)
              printf("DIRECTORY CLOSED: %s \n", event->name);
            else
              printf("FILE CLOSED %s \n", event->name);
          }
          if (event->mask & IN_MODIFY) {
            if (event->mask & IN_ISDIR)
              printf("DIRECTORY MODIFIED: %s \n", event->name);
            else
              printf("FILE MODIFIED %s \n", event->name);
          }
          if (event->mask & IN_CREATE) {
            if (event->mask & IN_ISDIR)
              printf("DIRECTORY CREATED: %s \n", event->name);
            else
              printf("FILE CREATED %s \n", event->name);
          }
          if (event->mask & IN_DELETE) {
            if (event->mask & IN_ISDIR)
              printf("DIRECTORY DELETED: %s \n", event->name);
            else
              printf("FILE DELETED %s \n", event->name);
          }
        }
        i += EVENT_SIZE + event->len;
      }
    }
    /* Освобождение ресурсов*/
    inotify_rm_watch(fd, wd);
    close(fd);
    return 0;
  }
}
// const char element[] = "/home/test1/Projects/C++/my_inotify/test.txt";

/* добавим наблюдение для директории
 *
 * Системный вызов inotifyadd_watch(int fd, const char *elementname,
 * uint32_t mask) добавляет новый элемент в список наблюдения для объекта
 * inotify, ссылка на который осуществляется с помощью файлового
 * дескриптора. Аргумент mask добавляет тип событий, которые должны
 * мониториться файловым дескриптором. Рассмотрим флаги событий, за которыми
 * можно наблюдать:
 *
 *
 *
 * */

// while (1) {
//   i = 0;
//   /* высчитываем размер файлового дескриптора*/
//   length = read(fd, buffer, BUF_LEN);
//   if (length < 0) {
//     perror("read");
//   }
//
//   while (i < length) {
//     struct inotify_event* event = (struct inotify_event* )&buffer[i];
//     if (event->len) {
//       if (event->mask & IN_CLOSE) {
//         if (event->mask & IN_ISDIR)
//           printf("The directory %s was closed.\n", event->name);
//         else
//           printf("The file %s was closed with WD %d\n", event->name,
//                  event->wd);
//       }
//       if (event->mask & IN_MODIFY) {
//         if (event->mask & IN_ISDIR)
//           printf("The directory %s was modified.\n", event->name);
//         else
//           printf("The file %s was modified with WD %d\n", event->name,
//                  event->wd);
//       }
//       i += EVENT_SIZE + event->len;
//     }
//   }
// }
/* Освобождение ресурсов*/
