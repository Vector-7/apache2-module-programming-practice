# apache2-module-programming-practice
C로 웹서버를 구현할 생각을 하는 걸 보니 니가 제정신이 아니구나?

## 개발환경, 프로젝트 생성/구동 (Ubuntu 기준)

1. Apache2 및 Apache2 개발도구 설치

```bash
sudo apt update
sudo apt install apache2
sudo apt install apache2-dev
```

2. 모듈 프로젝트 생성

```bash
apxs2 -g -n [프로젝트 이름]
```
3. mod_[프로젝트 이름].c 에 하고싶은거 만든 다음 모듈 컴파일

```bash
sudo make           # 모듈을 컴파일하고
sudo make install   # 컴파일된 모듈을 Apache Module Directory로 복사한다.
```

4. Apache의 설정파일인 apache2.conf의 맨 밑에 아래와 같은 내용을 추가한다.

```bash
LoadModule [프로젝트이름]_module /usr/lib/apache2/modules/[모듈이름].so
<Location /[프로젝트이름]>
    setHandler [프로젝트이름]
</Location>
```

5. Apache를 Reload한다
```bash
sudo apachectl restart 또는 sudo apachectl start
```

