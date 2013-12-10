#ifndef SCENARIOTEXTEDIT_H
#define SCENARIOTEXTEDIT_H

#include <UserInterface/Widgets/CompletableTextEdit/CompletableTextEdit.h>
#include "ScenarioTextBlock/ScenarioTextBlockStyle.h"

class QCompleter;


class ScenarioTextEdit : public CompletableTextEdit
{
	Q_OBJECT


public slots:
	void test();

public:
	explicit ScenarioTextEdit(QWidget* _parent = 0);

	/**
	 * @brief Установить вид текущего блока
	 * @param Тип блока
	 */
	void setScenarioBlockType(ScenarioTextBlockStyle::Type _blockType);

	/**
	 * @brief Получить вид блока
	 */
	ScenarioTextBlockStyle::Type scenarioBlockType(const QTextBlock& _block);

protected:
	/**
	 * @brief Нажатия многих клавиш обрабатываются вручную
	 */
	void keyPressEvent(QKeyEvent* _event);

	/**
	 * @brief Переопределяется для реализации увеличения/уменьшения текста
	 */
	void wheelEvent(QWheelEvent* _event);

private:
	/**
	 * @brief Изменить регистр текста, если это необходимо
	 */
	void makeTextUpper(QKeyEvent* _event);

	/**
	 * @brief Оканчивается ли строка сокращением
	 */
	bool stringEndsWithAbbrev(const QString& _text);
};

#endif // SCENARIOTEXTEDIT_H