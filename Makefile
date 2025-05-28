CXX = g++

CXXFLAGS = -Wall -Wextra -std=c++11 -g

SRC = Graph.cpp Algorithms.cpp Node_V.cpp PropertyQueue.cpp Queue.cpp UnionFind.cpp EdgeList.cpp

TEST = tests/memory_test.cpp tests/edgeList_test.cpp tests/helpers_test.cpp tests/node_v_test.cpp tests/propertyQueue_test.cpp tests/queue_test.cpp tests/unionFind_test.cpp tests/algorithms_test.cpp

INCLUDES = -I.

TARGET_MAIN = run_main
TARGET_TEST = run_test

.PHONY: all clean run-main run-test test main

all: $(TARGET_MAIN) $(TARGET_TEST)

$(TARGET_MAIN): $(SRC) main.cpp
	$(CXX) $(CXXFLAGS) $(SRC) main.cpp -o $(TARGET_MAIN) $(INCLUDES)

$(TARGET_TEST): $(SRC) $(TEST)
	$(CXX) $(CXXFLAGS) $(SRC) $(TEST) -o $(TARGET_TEST) $(INCLUDES)

run-main: $(TARGET_MAIN)
	./$(TARGET_MAIN)

run-test: $(TARGET_TEST)
	./$(TARGET_TEST)

test: run-test
main: run-main

valgrind: $(TARGET_TEST)
	valgrind --leak-check=full ./$(TARGET_TEST)

clean:
	rm -f $(TARGET_MAIN) $(TARGET_TEST)

# ========================================================================
# תוספת GUI למערכת - מוסיפה יכולות חדשות מבלי לשנות את הקיים!
# ========================================================================

# מקורות GUI (נוספים למה שכבר יש)
GUI_SOURCES = GraphVisualizer.cpp

# בדיקה חכמה אם SFML זמין במערכת
SFML_AVAILABLE := $(shell pkg-config --exists sfml-graphics sfml-window sfml-system 2>/dev/null && echo "yes" || echo "no")

# אם SFML זמין, הגדר דגלים
ifeq ($(SFML_AVAILABLE), yes)
    SFML_CFLAGS := $(shell pkg-config --cflags sfml-graphics sfml-window sfml-system)
    SFML_LIBS := $(shell pkg-config --libs sfml-graphics sfml-window sfml-system)
    SFML_DEFINE = -DSFML_AVAILABLE=1
    GUI_MESSAGE = "✅ SFML זמין - מערכת גרפית מופעלת"
else
    SFML_CFLAGS =
    SFML_LIBS =
    SFML_DEFINE = -DCONSOLE_ONLY=1
    GUI_MESSAGE = "⚠️  SFML לא זמין - מצב קונסולה בלבד"
endif

# ========================================================================
# יעדי GUI חדשים (לא משנים את הקיימים!)
# ========================================================================

# יעד ראשי למערכת הויזואליזציה - היברידי (GUI אם יש, קונסולה אם אין)
visualizer: $(SRC) $(GUI_SOURCES) main.cpp
	@echo $(GUI_MESSAGE)
	@if [ "$(SFML_AVAILABLE)" = "yes" ]; then \
		echo "🔨 בונה מערכת עם GUI..."; \
		$(CXX) $(CXXFLAGS) $(SRC) $(GUI_SOURCES) main.cpp -o visualizer $(INCLUDES) $(SFML_CFLAGS) $(SFML_LIBS) $(SFML_DEFINE); \
		echo "✅ מערכת הויזואליזציה נבנתה בהצלחה!"; \
		echo "🚀 הרץ עם: ./visualizer"; \
	else \
		echo "🔨 בונה מערכת קונסולית..."; \
		$(CXX) $(CXXFLAGS) $(SRC) main.cpp -o visualizer $(INCLUDES) $(SFML_DEFINE); \
		echo "✅ מערכת קונסולית נבנתה בהצלחה!"; \
		echo "🚀 הרץ עם: ./visualizer"; \
	fi

# יעד נוח להרצה ישירה של הויזואליזציה
run-visualizer: visualizer
	@echo "🎯 מפעיל מערכת ויזואליזציה..."
	./visualizer

# יעד ל-GUI בלבד (רק אם SFML זמין)
gui-only: $(SRC) $(GUI_SOURCES) main.cpp
	@if [ "$(SFML_AVAILABLE)" = "yes" ]; then \
		echo "🔨 בונה מערכת GUI..."; \
		$(CXX) $(CXXFLAGS) $(SRC) $(GUI_SOURCES) main.cpp -o gui_system $(INCLUDES) $(SFML_CFLAGS) $(SFML_LIBS) -DSFML_AVAILABLE=1; \
		echo "✅ מערכת GUI נבנתה!"; \
		echo "🚀 הרץ עם: ./gui_system"; \
	else \
		echo "❌ SFML לא זמין - התקן עם: sudo apt install libsfml-dev"; \
		exit 1; \
	fi

# בדיקת מערכת ומידע
info:
	@echo "📊 מידע על המערכת:"
	@echo "   SFML זמין: $(SFML_AVAILABLE)"
	@if [ "$(SFML_AVAILABLE)" = "yes" ]; then \
		echo "   גרסת SFML: $$(pkg-config --modversion sfml-graphics)"; \
	fi
	@echo "   קומפיילר: $(CXX)"
	@echo "   דגלים: $(CXXFLAGS)"
	@echo ""
	@echo "📋 יעדים זמינים:"
	@echo "   make main          - המטלה המקורית (ללא שינוי!)"
	@echo "   make test          - הרצת בדיקות (ללא שינוי!)"
	@echo "   make visualizer    - מערכת ויזואליזציה (חדש!)"
	@echo "   make run-visualizer- הרצה ישירה של הויזואליזציה"
	@echo "   make gui-only      - GUI בלבד (דורש SFML)"
	@echo "   make info          - מידע זה"
	@echo "   make install-sfml  - התקנת SFML (Ubuntu/Debian)"

# יעד נוח להתקנת SFML
install-sfml:
	@echo "📦 מתקין SFML..."
	@if command -v apt-get >/dev/null 2>&1; then \
		echo "Ubuntu/Debian מזוהה - מתקין עם apt..."; \
		sudo apt update && sudo apt install -y libsfml-dev; \
	elif command -v brew >/dev/null 2>&1; then \
		echo "macOS מזוהה - מתקין עם brew..."; \
		brew install sfml; \
	elif command -v pacman >/dev/null 2>&1; then \
		echo "Arch Linux מזוהה - מתקין עם pacman..."; \
		sudo pacman -S sfml; \
	else \
		echo "❌ מערכת הפעלה לא נתמכת אוטומטית"; \
		echo "התקן SFML ידנית: https://www.sfml-dev.org/download.php"; \
	fi
	@echo "✅ סיום התקנה - הרץ 'make info' לבדיקה"

# ניקוי מורחב (כולל קבצי GUI)
clean-all: clean
	@echo "🧹 מנקה קבצי GUI..."
	@rm -f visualizer gui_system
	@echo "✅ ניקוי הושלם"

# עזרה מורחבת
help-all: info

# ========================================================================
# הערות חשובות:
# 1. כל הפקודות המקוריות נשארות בדיוק כמו שהן!
# 2. make main - עדיין עובד בדיוק כמו קודם
# 3. make test - עדיין עובד בדיוק כמו קודם
# 4. רק נוספו פקודות חדשות למערכת הויזואליזציה
# ========================================================================

.PHONY: visualizer run-visualizer gui-only info install-sfml clean-all help-all