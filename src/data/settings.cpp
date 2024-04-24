#include "settings.h"
#include <QSettings>

bool Settings::winterMode() {
    QSettings set(SETTINGS_FILE, QSettings::IniFormat);
    if (!set.contains(WINTER_MODE_KEY))
        setWinterMode(WINTER_MODE_DEFAULT);
    return set.value(WINTER_MODE_KEY, WINTER_MODE_DEFAULT).toBool();
}

void Settings::setWinterMode(bool winterMode) {
    QSettings(SETTINGS_FILE, QSettings::IniFormat).setValue(WINTER_MODE_KEY, winterMode);
}

int Settings::winterPeriod() {
    QSettings set(SETTINGS_FILE, QSettings::IniFormat);
    if (!set.contains(WINTER_PERIOD_KEY))
        setWinterPeriod(WINTER_PERIOD_DEFAULT);
    return set.value(WINTER_PERIOD_KEY, WINTER_PERIOD_DEFAULT).toInt();
}

void Settings::setWinterPeriod(int winterPeriod) {
    QSettings(SETTINGS_FILE, QSettings::IniFormat).setValue(WINTER_PERIOD_KEY, winterPeriod);
}

int Settings::summerPeriod() {
    QSettings set(SETTINGS_FILE, QSettings::IniFormat);
    if (!set.contains(SUMMER_PERIOD_KEY))
        setSummerPeriod(SUMMER_PERIOD_DEFAULT);
    return set.value(SUMMER_PERIOD_KEY, SUMMER_PERIOD_DEFAULT).toInt();
}

void Settings::setSummerPeriod(int summerPeriod) {
    QSettings(SETTINGS_FILE, QSettings::IniFormat).setValue(SUMMER_PERIOD_KEY, summerPeriod);
}

int Settings::windowX() {
    QSettings set(SETTINGS_FILE, QSettings::IniFormat);
    if (!set.contains(POS_X_KEY))
        setWindowX(POS_X_DEFAULT);
    return set.value(POS_X_KEY, POS_X_DEFAULT).toInt();
}

void Settings::setWindowX(int windowX) {
    QSettings(SETTINGS_FILE, QSettings::IniFormat).setValue(POS_X_KEY, windowX);
}

int Settings::windowY() {
    QSettings set(SETTINGS_FILE, QSettings::IniFormat);
    if (!set.contains(POS_Y_KEY))
        setWindowY(POS_Y_DEFAULT);
    return set.value(POS_Y_KEY, POS_Y_DEFAULT).toInt();
}

void Settings::setWindowY(int windowY) {
    QSettings(SETTINGS_FILE, QSettings::IniFormat).setValue(POS_Y_KEY, windowY);
}

int Settings::windowWidth() {
    QSettings set(SETTINGS_FILE, QSettings::IniFormat);
    if (!set.contains(WIDTH_KEY))
        setWindowWidth(WIDTH_DEFAULT);
    return set.value(WIDTH_KEY, WIDTH_DEFAULT).toInt();
}

void Settings::setWindowWidth(int windowWidth) {
    QSettings(SETTINGS_FILE, QSettings::IniFormat).setValue(WIDTH_KEY, windowWidth);
}

int Settings::windowHeight() {
    QSettings set(SETTINGS_FILE, QSettings::IniFormat);
    if (!set.contains(HEIGHT_KEY))
        setWindowHeight(HEIGHT_DEFAULT);
    return set.value(HEIGHT_KEY, HEIGHT_DEFAULT).toInt();
}

void Settings::setWindowHeight(int windowHeight) {
    QSettings(SETTINGS_FILE, QSettings::IniFormat).setValue(HEIGHT_KEY, windowHeight);
}

QString Settings::dataBasePath() {
    QSettings set(SETTINGS_FILE, QSettings::IniFormat);
    if (!set.contains(DATABASE_PATH_KEY))
        setDataBasePath(DATABASE_PATH_DEFAULT);
    return set.value(DATABASE_PATH_KEY, DATABASE_PATH_DEFAULT).toString();
}

void Settings::setDataBasePath(const QString &dataBasePath) {
    QSettings(SETTINGS_FILE, QSettings::IniFormat).setValue(DATABASE_PATH_KEY, dataBasePath);
}

int Settings::currentPeriod()
{
    return winterMode() ? winterPeriod() : summerPeriod();
}

bool Settings::columnVisible(int column)
{
    QString key = COLUMN_VISIBLE_KEY + QString::number(column);
    QSettings set(SETTINGS_FILE, QSettings::IniFormat);
    if (!set.contains(key))
        setWinterMode(COLUMN_VISIBLE_DEFAULT);
    return set.value(key, COLUMN_VISIBLE_DEFAULT).toBool();
}

void Settings::setColumnVisible(int column, bool visibled)
{
    QString key = COLUMN_VISIBLE_KEY + QString::number(column);
    QSettings(SETTINGS_FILE, QSettings::IniFormat).setValue(key, visibled);
}
