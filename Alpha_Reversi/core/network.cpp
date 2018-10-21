#include "network.h"

std::string create_session(int num) {
    std::string content = "create_session/" + std::to_string(num);
    std::string res;
    res = network(content);
    return res;
}

std::string board_string(int num) {
    std::string content = "board_string/" + std::to_string(num);
    std::string res;
    res = network(content);
    return res;
}

std::string get_move(int x, int y, int num, std::string color) {
    std::string content = "move/" + std::to_string(num) + "/" + std::to_string(x) + "/" + std::to_string(y) + "/" + color;
    std::string res;
    res = network(content);
    return res;
}

std::string get_trun(int num) {
    std::string content = "turn/" + std::to_string(num);
    std::string res;
    res = network(content);
    return res;
}

std::string network(std::string content) {
    int sockfd, ret, i, h;
    std::string res;
    struct sockaddr_in servaddr;
    char str1[4096], str2[4096], buf[BUFSIZE], *str;
    socklen_t len;
    fd_set t_set1;
    struct timeval tv;

    //创建套接字
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("socket error!\n");
        exit(0);
    };

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, IPSTR, &servaddr.sin_addr) <= 0) {
        printf("inet_pton error!\n");
        exit(0);
    };

    if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
        printf("connect error!\n");
        exit(0);
    }

    memset(str1, 0, 4096);
    strcat(str1, "GET ");
    strcat(str1, content.c_str());
    strcat(str1, " HTTP/1.1 \r\n\r\n");
    printf("%s", str1);

    ret = write(sockfd, str1, strlen(str1));
    if (ret < 0) {
        printf("Get failed！error is %d，error message: '%s'\n", errno, strerror(errno));
        exit(0);
    } else {
        printf("Get %d bytes successfully！\n\n", ret);
    }

    FD_ZERO(&t_set1);
    FD_SET(sockfd, &t_set1);

    while (true) {
        sleep(2);
        tv.tv_sec = 0;
        tv.tv_usec = 0;
        h = 0;
        h = select(sockfd + 1, &t_set1, NULL, NULL, &tv);
        if (h < 0) {
            close(sockfd);
            printf("select error! \n");
            return NULL;
        } else if (h > 0) {
            memset(buf, 0, 4096);
            i = read(sockfd, buf, 4095);
            if (i == 0) {
                close(sockfd);
                printf("connetion close! \n");
                return NULL;
            } else {
                res = buf;
                break;
            }
        }
    }
    std::string newres;
    for (int i = res.length(); i > 0; --i) {
        if (res[i] == '\n') {
            newres = res.substr(i+1, res.length());
            break;
        }
    }
    std::cout << newres << std::endl;
    return newres;
}