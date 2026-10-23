#define PI 3.14159265358979323846
#include <conio.h>
#include <graphics.h>
#include <time.h>
#include <cmath>
#include <algorithm>

//SDF实现线段抗锯齿
void drawLineAA(int x1, int y1, int x2, int y2, COLORREF color, int width = 1) {
    int minX = (std::min)(x1, x2) - width - 1, maxX = (std::max)(x1, x2) + width + 1;
    int minY = (std::min)(y1, y2) - width - 1, maxY = (std::max)(y1, y2) + width + 1;
    float dx = x2 - x1, dy = y2 - y1;
    float len2 = dx * dx + dy * dy;
    if (len2 == 0) return;

    for (int y = minY; y <= maxY; ++y) {
        for (int x = minX; x <= maxX; ++x) {
            float pax = x - x1, pay = y - y1;
            float bax = dx, bay = dy;
            float h = (pax * bax + pay * bay) / len2;
            h = (std::max)(0.0f, (std::min)(1.0f, h));
            float projx = x1 + bax * h;
            float projy = y1 + bay * h;
            float dist = sqrtf((x - projx) * (x - projx) + (y - projy) * (y - projy));
            float d = fabs(dist - width / 2.0f);

            if (d < 1.0f) {
                float alpha = 1.0f - d;
                COLORREF bg = getpixel(x, y);
                BYTE r1 = GetRValue(color), g1 = GetGValue(color), b1 = GetBValue(color);
                BYTE r2 = GetRValue(bg), g2 = GetGValue(bg), b2 = GetBValue(bg);
                BYTE fr = (BYTE)(r1 * alpha + r2 * (1 - alpha));
                BYTE fg = (BYTE)(g1 * alpha + g2 * (1 - alpha));
                BYTE fb = (BYTE)(b1 * alpha + b2 * (1 - alpha));
                putpixel(x, y, RGB(fr, fg, fb));
            }
        }
    }
}

//SDF实现圆形抗锯齿
void drawCircleAA(int cx, int cy, int r, COLORREF color) {
    for (int y = -r - 1; y <= r + 1; ++y) {
        for (int x = -r - 1; x <= r + 1; ++x) {
            float dist = sqrtf((float)(x * x + y * y));
            float d = fabs(dist - r);
            if (d < 1.0f) {
                float alpha = 1.0f - d;
                COLORREF bg = getpixel(cx + x, cy + y);
                BYTE r1 = GetRValue(color), g1 = GetGValue(color), b1 = GetBValue(color);
                BYTE r2 = GetRValue(bg), g2 = GetGValue(bg), b2 = GetBValue(bg);
                BYTE fr = (BYTE)(r1 * alpha + r2 * (1 - alpha));
                BYTE fg = (BYTE)(g1 * alpha + g2 * (1 - alpha));
                BYTE fb = (BYTE)(b1 * alpha + b2 * (1 - alpha));
                putpixel(cx + x, cy + y, RGB(fr, fg, fb));
            }
        }
    }
}

struct ClockStyle {
    int centerX, centerY;
    int radius;
    COLORREF dialColor;
    int hourLen, minLen, secLen;
    COLORREF hourColor, minColor, secColor;
    int hourWidth, minWidth, secWidth;
    int petalCount = 12;
    int petalLen = 100;
    COLORREF petalColor;
};

class TimeManager {
private:
    int hour, minute, second;
public:
    void update() {
        time_t now;
        struct tm t;
        time(&now);
        localtime_s(&t, &now);
        hour = t.tm_hour % 12;
        minute = t.tm_min;
        second = t.tm_sec;
    }
    double getHourAngle() { return (hour * 30 + minute * 0.5) * PI / 180; }
    double getMinuteAngle() { return (minute * 6 + second * 0.1) * PI / 180; }
    double getSecondAngle() { return second * 6 * PI / 180; }
};

class ClockDrawer {
private:
    ClockStyle style;
    TimeManager time;

    void drawBackground() {
        int winWidth = getwidth();
        int winHeight = getheight();
        int centerX = winWidth / 2;
        int centerY = winHeight / 2;
        int maxR = (int)sqrt((float)(centerX * centerX + centerY * centerY));

        for (int r = 0; r <= maxR; r++) {
            float ratio = (float)r / maxR;
            int red = (int)(255 - 140 * ratio);
            int green = (int)(255 - 128 * ratio);
            int blue = (int)(255 - 225 * ratio);
            setcolor(RGB(red, green, blue));
            circle(centerX, centerY, r);
        }
    }

    void drawflowerPetals() {
        int r = style.petalLen / 2;
        int baseR = style.radius;
        const int SEGMENTS = 30;
        double petalAngle = 30 * PI / 180;
        for (int i = 0; i < style.petalCount; i++) {
            double centerAngle = i * 30 * PI / 180;
            int cx = style.centerX + baseR * sin(centerAngle);
            int cy = style.centerY - baseR * cos(centerAngle);
            POINT petal[2 * SEGMENTS + 2];
            for (int j = 0; j <= SEGMENTS; ++j) {
                double theta = centerAngle - petalAngle / 2 + petalAngle * j / SEGMENTS;
                int x = style.centerX + baseR * sin(theta);
                int y = style.centerY - baseR * cos(theta);
                petal[j] = { x, y };
            }
            double baseAngle = centerAngle + PI;
            for (int j = 0; j <= SEGMENTS; ++j) {
                double theta = baseAngle + PI * j / SEGMENTS;
                int x = cx + r * cos(theta);
                int y = cy + r * sin(theta);
                petal[SEGMENTS + 1 + j] = { x, y };
            }
            setfillcolor(style.petalColor);
            setlinecolor(style.petalColor);
            fillpolygon(petal, 2 * SEGMENTS + 2);
        }
    }

public:
    ClockDrawer(ClockStyle s) : style(s) {}

    void drawDial() {
        setfillcolor(style.dialColor);
        fillcircle(style.centerX, style.centerY, style.radius);
        for (int i = 0; i < 60; i++) {
            double angle = i * 6 * PI / 180;
            int outerR = style.radius;
            int innerR = (i % 5 == 0) ? outerR - 15 : outerR - 8;
            int markWidth = (i % 5 == 0) ? 4 : 2;
            COLORREF markColor = RGB(140, 70, 20);
            int x1 = style.centerX + innerR * sin(angle);
            int y1 = style.centerY - innerR * cos(angle);
            int x2 = style.centerX + outerR * sin(angle);
            int y2 = style.centerY - outerR * cos(angle);

            if (i % 30 == 0) {
                for (int w = 0; w < markWidth; ++w) {
                    drawLineAA(x1 + w - markWidth / 2, y1, x2 + w - markWidth / 2, y2, markColor);
                }
            }
            else {
                for (int w = 0; w < markWidth; ++w) {
                    drawLineAA(x1, y1 + w - markWidth / 2, x2, y2 + w - markWidth / 2, markColor);
                }
            }
        }
        drawflowerPetals();
    }

    void drawHands() {
        time.update();
        double hAngle = time.getHourAngle();
        int hx = style.centerX + style.hourLen * sin(hAngle);
        int hy = style.centerY - style.hourLen * cos(hAngle);
        for (int w = 0; w < style.hourWidth; ++w)
            drawLineAA(style.centerX, style.centerY + w - style.hourWidth / 2, hx, hy + w - style.hourWidth / 2, style.hourColor);
        setfillcolor(RGB(245, 180, 0));
        fillcircle(hx, hy, 4);
        drawCircleAA(hx, hy, 4, style.hourColor);

        double mAngle = time.getMinuteAngle();
        int mx = style.centerX + style.minLen * sin(mAngle);
        int my = style.centerY - style.minLen * cos(mAngle);
        for (int w = 0; w < style.minWidth; ++w)
            drawLineAA(style.centerX, style.centerY + w - style.minWidth / 2, mx, my + w - style.minWidth / 2, style.minColor);
        setfillcolor(RGB(250, 190, 10));
        fillcircle(mx, my, 3);
        drawCircleAA(mx, my, 3, style.minColor);

        double sAngle = time.getSecondAngle();
        int sx = style.centerX + style.secLen * sin(sAngle);
        int sy = style.centerY - style.secLen * cos(sAngle);
        for (int w = 0; w < style.secWidth; ++w)
            drawLineAA(style.centerX, style.centerY + w - style.secWidth / 2, sx, sy + w - style.secWidth / 2, style.secColor);
        setfillcolor(RGB(255, 215, 0));
        fillcircle(sx, sy, 5);
        drawCircleAA(sx, sy, 5, RGB(200, 160, 0));

        setfillcolor(RGB(250, 204, 0));
        fillcircle(style.centerX, style.centerY, 6);
        drawCircleAA(style.centerX, style.centerY, 6, RGB(255, 220, 0));
    }

    void refresh() {
        cleardevice();
        drawBackground();
        drawDial();
        drawHands();
        FlushBatchDraw();
    }
};

int main() {
    initgraph(800, 800);
    BeginBatchDraw();
    setbkcolor(RGB(255, 250, 240));
    cleardevice();

    ClockStyle style = {
        400, 400, 200,
        RGB(255, 245, 220),
        120, 160, 180,
        RGB(200, 160, 0),
        RGB(230, 190, 0),
        RGB(255, 220, 0),
        6, 4, 1,
        12, 100,
        RGB(255, 210, 0),
    };

    ClockDrawer clock(style);
    while (!_kbhit()) {
        clock.refresh();
        Sleep(100);
    }

    EndBatchDraw();
    closegraph();
    return 0;
}