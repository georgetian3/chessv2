#ifndef AI_HPP
#define AI_HPP

#include "square.hpp"

class AI: public QObject {

    Q_OBJECT

    const std::vector<std::vector<Square*>>& squares_;
    const std::vector<QPoint> moves_ = {
        QPoint(0, 1),
        QPoint(1, 0),
        QPoint(-1, 0)
    };

    // 实际实现AI算法并对棋子做操作的函数
    // 能传入目前的级别，让AI做出对应的复杂度的操作
    void algorithm(int level);


public:

    // 构造AI时传递Board类的squares_变量的常引用，
    // 这一个变量足以表示游戏所有方面的状态
    AI(const std::vector<std::vector<Square*>>& squares);

public slots:

    // 为了避免将界面卡死，让AI在新的一个线程里运行。
    void run(int level);


signals:

    // 用户通过点击按钮，发出信号调用Board中的槽函数，
    // 而AI在algorithm中直接发出信号调用Board中的槽函数
    void squareClicked(Square*);
    void attackClicked();
    void spellClicked();
    void selectClicked();
    void skipClicked();

};

#endif // AI_HPP
