#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

// =================متغيرات هديها قيمه اسميهم بيوضحو هما بتوع اي=================
int level = 1;
int score = 0;
int targetscore[3] = { 250, 450, 650 };
bool enterPressedOnce = false;

// =================انو ينتقل بين اليفل وتاني================
bool canGoNextLevel() {
    return score >= targetscore[level - 1];
}

void nextLevel() {
    if (canGoNextLevel() && level < 3) {
        level++;
        score = 0;
    }
}

void handleLevelInput(bool enterPressed) {
    if (enterPressed) {
        if (!enterPressedOnce) {
            nextLevel();
            enterPressedOnce = true;
        }
    }
    else {
        enterPressedOnce = false;
    }
}

// =================بنزود سرعه الاخصام عشان الاعبيط الي هيلعب يستمتع=================
float getEnemySpeed() {
    if (level == 1) return 2.0f;
    if (level == 2) return 3.0f;
    if (level == 3) return 4.5f;
    return 2.0f;
}

// ================= نظام الاسكور =================
void addScore(int value) {
    score += value;
}

// =================عشان نطلع اعلي سكور  =================
struct Player {
    string name;
    int score;
};

vector<Player> highScores;

void loadScores() {
    ifstream file("scores.txt");
    highScores.clear();

    Player p;
    while (file >> p.name >> p.score) {
        highScores.push_back(p);
    }
    file.close();
}

void saveScores() {
    ofstream file("scores.txt");

    for (auto& p : highScores) {
        file << p.name << " " << p.score << endl;
    }
    file.close();
}

void updateHighScores(string name, int newScore) {
    highScores.push_back({ name, newScore });

    sort(highScores.begin(), highScores.end(),
        [](Player a, Player b) {
            return a.score > b.score;
        });

    if (highScores.size() > 5) {
        highScores.resize(5);
    }
}

// ================= نعيد تشغيل سيستم===========
void resetGame() {
    level = 1;
    score = 0;
}