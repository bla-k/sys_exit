#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

#define BLK_SZ   6
#define BUF_SZ   80
#define COLS     80
#define ROWS     40
#define YEARS_OF_CHRIST 33

float _m_data_a[] = {
    -0.12949f, -0.15460f, -0.08210f, 0.40467f, -0.03995f, -0.26771f, -0.02097f,
    0.33675f, -0.00341f, 0.37425f, -0.34738f, 0.01625f, -2.82923f, 1.57834f,
    -0.10420f, 0.24084f, -0.05603f, -0.09973f, 8.60548f, -3.86065f, 0.16257f,
    -0.25768f, 0.00957f, -0.30628f, -0.35942f, -0.73232f, -0.15202f, 0.20677f,
    0.05441f, 0.24201f, -0.09377f, 0.28469f, 0.20865f, 0.38768f, 0.31331f,
    0.85282f, -3.03171f, -0.45778f, 0.21993f, -0.25575f, -1.28545f, -0.63561f,
    -0.18575f, 0.35988f, 2.41605f, -7.20874f, -0.15165f, -0.84367f, 0.32114f,
    -0.15273f, -0.11214f, 0.05282f, -5.34605f, -4.05737f, -0.02861f, -0.36721f,
    -0.09942f, 0.29996f, 0.19269f, -0.01080f, 0.48818f, -0.19701f, -0.03114f,
    0.29133f, -2.66936f, -5.06173f, -0.01787f, -0.02685f, -0.13086f, -0.33949f,
    0.00929f, -0.10884f, -0.09711f, 0.17611f, -0.21373f, -0.66915f, -0.05541f,
    0.18057f, 0.01385f, 0.27147f, 7.18515f, -2.78711f, -0.03608f, -0.41221f,
    -0.03172f, 0.25488f, 0.19374f, -0.62493f, 0.00914f, 0.20420f, -0.16842f,
    -0.17896f, 1.02988f, 3.97349f, 0.12689f, 0.25516f, -0.43198f, -6.30069f,
    0.05005f, -0.23994f, 0.14678f, -0.34747f, 0.03573f, 0.29802f, 0.11871f,
    -0.25736f, -0.10955f, 0.23918f, 0.31912f, -0.09478f, -0.08321f, 0.27638f,
    -0.00173f, -0.27878f, 0.11911f, -0.26155f, -0.07479f, -0.50555f, 0.23667f,
    0.01333f, 0.06212f, -0.43831f, -0.12298f, 0.07372f, -0.10090f, 0.22949f,
    0.07993f, 0.20056f, -0.12628f, -0.23686f, -0.10985f, 0.26838f, -0.58410f,
    0.79077f, -0.04207f, 0.15535f, 0.00552f, 0.24188f, 5.39578f, 1.90536f,
    0.12575f, -0.26439f, -0.01874f, -0.37174f, -0.24777f, 0.54594f, -0.49584f,
    0.63353f, -0.00533f, 0.23352f, -0.22603f, 0.08324f, 1.11220f, 0.86253f,
    -0.13368f, 0.27776f, -2.86266f, -0.94777f, -4.49768f, 9.94976f
};

float _m_data_b[] = {
    -0.45782f, 0.13866f, -0.45805f, 0.49648f, 0.30609f, -0.01966f, -2.40760f,
    1.29504f, -0.29268f, -0.03022f, -0.17100f, -0.52331f, 0.02247f, 0.01596f,
    0.51127f, 0.93927f, 0.13909f, -0.06540f, 2.02549f, -0.11805f, 0.40378f,
    1.07415f, 2.41788f, -0.06527f, -0.08050f, -0.13521f, 0.82094f, -0.02529f,
    0.90448f, 0.11453f, -0.01304f, 0.29805f, 3.18668f, -0.09872f, 0.01475f,
    -0.23408f, 0.12151f, -0.03126f, -0.05737f, 0.36067f, -3.59875f, -0.26562f,
    0.63062f, -0.20507f, 0.62463f, -0.03774f, -1.78780f, -0.02517f, 0.74834f,
    -0.85008f, -0.92334f, 0.30847f, -1.29190f, 1.58172f, -0.00430f, 0.88805f,
    -0.60399f, -1.25266f, -0.11201f, 0.11346f, -0.40417f, -0.11721f, 1.59292f,
    0.47992f, -0.28766f, 1.07248f, -0.26560f, -0.06170f, 0.16208f, 4.63834f,
    -1.30537f, -0.40866f, 0.18328f, 0.31293f, 0.67730f, -0.01948f, -0.37697f,
    1.26155f, 0.29035f, 5.32319f
};

float _m_data_c[] = {
    0.41642f, -0.18454f, 0.43863f, -0.47809f, -0.31623f, 0.08585f, -1.78876f,
    -1.43943f, 0.25134f, 4.15048f, 0.14441f, 0.49607f, 0.35279f, -0.02954f,
    -0.48767f, -0.91769f, -0.26071f, -0.40967f, 2.58635f, 0.10402f, 0.75603f,
    -1.10416f, 4.63986f, 0.37400f, 0.02361f, 0.10575f, 4.51522f, 0.11362f,
    -0.88137f, -0.11131f, -0.03747f, -0.28600f, -3.49991f, 0.07912f, 0.11338f,
    0.20261f, -0.11383f, 0.30779f, 0.01156f, -0.34979f, -5.72464f, 0.30859f,
    -0.57358f, 0.23288f, -0.56281f, 0.09743f, 1.91764f, -0.07568f, -4.55470f,
    0.80608f, 0.90846f, -0.31868f, 1.43300f, -2.01183f, -0.03285f, -0.86475f,
    0.56965f, 1.36778f, 0.23713f, -0.13631f, 0.40565f, 0.08302f, -2.03863f,
    -0.44903f, 0.30204f, -1.08221f, 0.04419f, 0.02530f, -0.17395f, 4.90001f,
    1.45696f, 0.41652f, -0.18480f, -0.18696f, -0.62814f, 0.03360f, -0.80098f,
    -1.37313f, 1.80589f, 7.52869f
};

float _m_data_d[] = { -2.63960f };

char _p_load[] = {
    0xe0, 0x90, 0xff, 0x9c, 0xf4, 0xd4, 0xe5, 0xd5, 0xf5, 0xb6, 0xd9, 0xb4,
    0xc4, 0xa8, 0xcd, 0xb9, 0xdc, 0xf2, 0xd2, 0x85, 0xe0, 0x89, 0xee, 0x86,
    0xf2, 0x81, 0xa1, 0xf2, 0x93, 0xe5, 0x80, 0xe4, 0xca, 0xea, 0x8f, 0xf7,
    0x9e, 0xea, 0xc2, 0xf2, 0xdb
};

struct termios _t_orig;

void check_term(void) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    if (w.ws_col < COLS || w.ws_row < ROWS) {
        printf("ERR: Terminal too small.\n");
        printf("required %dx%d\n", COLS, ROWS);
        printf(" current %dx%d\n", w.ws_col, w.ws_row);
        _exit(1);
    }
}

float checksum(float x, float y) {
    float buf[BUF_SZ];

    for (int j = 0; j < BUF_SZ; j++) {
        float v = (x * _m_data_a[j * 2]) + (y * _m_data_a[j * 2 + 1]) + _m_data_b[j];
        buf[j] = tanhf(v);
    }

    float acc = 0.0;
    for (int j = 0; j < BUF_SZ; j++) acc += buf[j] * _m_data_c[j];

    acc += _m_data_d[0];

    return 1.0 / (1.0 + expf(-acc));
}

void dump(void) {
    const char _lut[] = " .:/0@";

    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            float nx = ((float)c / (COLS - 1)) * 2.0 - 1.0;
            float ny = ((float)r / (ROWS - 1)) * 2.0 - 1.0;

            float val = checksum(nx, ny);

            int j = (int)(val * (BLK_SZ - 1));
            if (j < 0) j = 0;
            if (j >= BLK_SZ) j = BLK_SZ - 1;

            putchar(_lut[j]);
            fflush(stdout);
            usleep(500);
        }
        putchar('\n');
    }
}

void flush(void) {
    for (int j = ROWS; j > 0; j--) {
        printf("\r\x1b[K\x1b[1A");
        fflush(stdout);
        usleep(40000);
    }
}

void sys_init(void) {
    check_term();
    tcgetattr(STDIN_FILENO, &_t_orig);
    struct termios raw = _t_orig;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void sys_restore() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &_t_orig);
}

void _h_sig() {
    sys_restore();
    write(STDOUT_FILENO, "\x1b[?25h\n", 7);
    _exit(0);
}

void sys_sig(void) {
    struct sigaction sa;
    sa.sa_handler = _h_sig;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
}

void decrypt(void) {
    int l = sizeof(_p_load) / sizeof(_p_load[0]);
    int o_c = (COLS - l - (l/4)) / 2;
    int o_r = ROWS / 2;

    printf("\x1b[%dA\r\x1b[%dC\x1b[1;32m", o_r, o_c);

    char k = 0xa5;
    int acc = 1500000;
    for (int j = 0; j < l; j++) {
        char c = _p_load[j];
        char d = c ^ k;
        k = c;

        putchar(d);
        fflush(stdout);
        usleep(50000);

        if (d == 0x2e) {
            usleep(acc);
            acc *= 2;
        }

        if (j == YEARS_OF_CHRIST) {
            printf("\x1b[1;31m");
        }
    }

    printf("\x1b[1B\r\x1b[%dC\x1b[%dB\r\x1b[0m", o_c, o_r);
    fflush(stdout);
}

int main() {
    sys_sig();
    sys_init();

    printf("\x1b[?25l\x1b[2J\x1b[1;1H");

    dump();

    usleep(500000);
    printf("\x1b[?25h");

    decrypt();

    printf("\x1b[?25l");
    flush();

    sys_restore();
    printf("\x1b[?25h");

    return 0;
}

