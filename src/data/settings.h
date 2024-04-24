#ifndef SETTINGS_H
#define SETTINGS_H

#define SETTINGS_FILE "settings.ini"
#define WINTER_MODE_KEY "Settings/WinterMode"
#define WINTER_MODE_DEFAULT false
#define WINTER_PERIOD_KEY "Settings/WinterPeriod"
#define WINTER_PERIOD_DEFAULT 28
#define SUMMER_PERIOD_KEY "Settings/SummerPeriod"
#define SUMMER_PERIOD_DEFAULT 14
#define POS_X_KEY "Geometry/X"
#define POS_X_DEFAULT 100
#define POS_Y_KEY "Geometry/Y"
#define POS_Y_DEFAULT 100
#define WIDTH_KEY "Geometry/Width"
#define WIDTH_DEFAULT 800
#define HEIGHT_KEY "Geometry/Height"
#define HEIGHT_DEFAULT 600
#define DATABASE_PATH_KEY "Base/Path"
#define DATABASE_PATH_DEFAULT "base.db"
#define COLUMN_VISIBLE_KEY "Columns/Column_"
#define COLUMN_VISIBLE_DEFAULT true

class QString;

class Settings {
    public:
        static bool winterMode();
        static void setWinterMode(bool winterMode);

        static int winterPeriod();
        static void setWinterPeriod(int winterPeriod);

        static int summerPeriod();
        static void setSummerPeriod(int summerPeriod);

        static int windowX();
        static void setWindowX(int windowX);

        static int windowY();
        static void setWindowY(int windowY);

        static int windowWidth();
        static void setWindowWidth(int windowWidth);

        static int windowHeight();
        static void setWindowHeight(int windowHeight);

        static QString dataBasePath();
        static void setDataBasePath(const QString &dataBasePath);

        static int currentPeriod();

        static bool columnVisible(int column);
        static void setColumnVisible(int column, bool visibled);
};

#endif // SETTINGS_H
