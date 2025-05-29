# קומפילר ודגלים
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g
INCLUDES = -I.

# ===== קבצי מקור - המחלקות המקוריות שלך (לא נוגעים!) =====
CORE_SOURCES = Graph.cpp Algorithms.cpp Node_V.cpp PropertyQueue.cpp Queue.cpp UnionFind.cpp EdgeList.cpp

# ===== קבצי המערכת החינוכית החדשה =====
GAME_SOURCES = GraphGameVisualizer.cpp

# ===== קבצי בדיקות (נשארים כמו שהם) =====
TEST_SOURCES = tests/memory_test.cpp tests/edgeList_test.cpp tests/helpers_test.cpp \
               tests/node_v_test.cpp tests/propertyQueue_test.cpp tests/queue_test.cpp \
               tests/unionFind_test.cpp tests/algorithms_test.cpp tests/graph_test.cpp

# =========================
# בודק אם SFML מותק
# =========================
SFML_AVAILABLE := $(shell pkg-config --exists sfml-graphics sfml-window sfml-system 2>/dev/null && echo yes || echo no)

ifeq ($(SFML_AVAILABLE), yes)
	SFML_CFLAGS := $(shell pkg-config --cflags sfml-graphics sfml-window sfml-system)
	SFML_LIBS := $(shell pkg-config --libs sfml-graphics sfml-window sfml-system)
	SFML_DEFINE = -DSFML_AVAILABLE=1
	GUI_MESSAGE = "✅ SFML זמין - מערכת המשחק החינוכי מופעלת"
else
	SFML_CFLAGS =
	SFML_LIBS =
	SFML_DEFINE = -DCONSOLE_ONLY=1
	GUI_MESSAGE = "⚠️  SFML לא זמין - מצב קונסולה בלבד"
endif

# קבצים בינאריים
TARGET_MAIN = GraphAlgorithmsGame
TARGET_TEST = GraphTests
TARGET_ORIGINAL = OriginalDemo

# =========================
# יעדים עיקריים
# =========================
.PHONY: all game test original clean clean-all run-game run-test run-original \
        info install-sfml help random-graph step-mode auto-mode

# יעד ברירת מחדל - המערכת החינוכי המלאה
all: $(TARGET_MAIN)

# ===== המערכת החינוכית הראשית =====
$(TARGET_MAIN): $(CORE_SOURCES) $(GAME_SOURCES) main.cpp
	@echo $(GUI_MESSAGE)
	@if [ "$(SFML_AVAILABLE)" = "yes" ]; then \
		echo "🎮 בונה מערכת לימוד אינטראקטיבית..."; \
		$(CXX) $(CXXFLAGS) $(CORE_SOURCES) $(GAME_SOURCES) main.cpp -o $(TARGET_MAIN) \
		$(INCLUDES) $(SFML_CFLAGS) $(SFML_LIBS) $(SFML_DEFINE); \
		echo "✅ מערכת המשחק החינוכי נבנתה בהצלחה!"; \
		echo "🎯 הרץ עם: ./$(TARGET_MAIN)"; \
	else \
		echo "📝 בונה מערכת קונסולית..."; \
		$(CXX) $(CXXFLAGS) $(CORE_SOURCES) main.cpp -o $(TARGET_MAIN) \
		$(INCLUDES) $(SFML_DEFINE); \
		echo "✅ מערכת קונסולית נבנתה בהצלחה!"; \
		echo "🖥️  הרץ עם: ./$(TARGET_MAIN) --console"; \
	fi

# ===== מערכת הבדיקות (נשארת כמו שהיתה) =====
$(TARGET_TEST): $(CORE_SOURCES) $(TEST_SOURCES)
	@echo "🧪 בונה מערכת בדיקות..."
	$(CXX) $(CXXFLAGS) $(CORE_SOURCES) $(TEST_SOURCES) -o $(TARGET_TEST) $(INCLUDES)
	@echo "✅ מערכת בדיקות נבנתה!"

# ===== הדגמה מקורית (ללא GUI) =====
$(TARGET_ORIGINAL): $(CORE_SOURCES)
	@echo "📚 בונה הדגמה מקורית..."
	@echo '#include "Graph.h"' > demo_main.cpp
	@echo '#include "Algorithms.h"' >> demo_main.cpp
	@echo '#include <iostream>' >> demo_main.cpp
	@echo 'int main() {' >> demo_main.cpp
	@echo '    using namespace graph;' >> demo_main.cpp
	@echo '    Graph g(4);' >> demo_main.cpp
	@echo '    g.add_Edge(0,1,2); g.add_Edge(1,2,3); g.add_Edge(2,3,1);' >> demo_main.cpp
	@echo '    std::cout << "Original Graph:" << std::endl; g.print_graph();' >> demo_main.cpp
	@echo '    Graph bfs = Algorithms::bfs(g, g.nodes[0]);' >> demo_main.cpp
	@echo '    std::cout << "BFS Tree:" << std::endl; bfs.print_graph();' >> demo_main.cpp
	@echo '    return 0;' >> demo_main.cpp
	@echo '}' >> demo_main.cpp
	$(CXX) $(CXXFLAGS) $(CORE_SOURCES) demo_main.cpp -o $(TARGET_ORIGINAL) $(INCLUDES)
	@rm demo_main.cpp
	@echo "✅ הדגמה מקורית נבנתה!"

# =========================
# יעדי הרצה
# =========================

# הרצת המערכת החינוכית
game: run-game
run-game: $(TARGET_MAIN)
	@echo "🎮 מפעיל מערכת לימוד אלגוריתמי גרפים..."
	@if [ "$(SFML_AVAILABLE)" = "yes" ]; then \
		echo "🎨 פותח חלון אינטראקטיבי..."; \
		./$(TARGET_MAIN); \
	else \
		echo "📝 מרץ במצב קונסולה..."; \
		./$(TARGET_MAIN) --console; \
	fi

# הרצת בדיקות
test: run-test
run-test: $(TARGET_TEST)
	@echo "🧪 מריץ בדיקות המערכת..."
	./$(TARGET_TEST)

# הרצת הדגמה מקורית
original: run-original
run-original: $(TARGET_ORIGINAL)
	@echo "📚 מריץ הדגמה של האלגוריתמים המקוריים..."
	./$(TARGET_ORIGINAL)

# מצבי הרצה מיוחדים של המערכת החינוכית
step-mode: $(TARGET_MAIN)
	@echo "👣 מצב צעד אחר צעד (ברירת מחדל)"
	./$(TARGET_MAIN)

auto-mode: $(TARGET_MAIN)
	@echo "⚡ מצב אוטומטי מהיר"
	./$(TARGET_MAIN) --fast

console-demo: $(TARGET_MAIN)
	@echo "🖥️  הדגמה בקונסולה"
	./$(TARGET_MAIN) --console

random-graph: $(TARGET_MAIN)
	@echo "🎲 יצירת גרף אקראי"
	./$(TARGET_MAIN) --random

# =========================
# Valgrind לבדיקת זיכרון
# =========================
valgrind: $(TARGET_TEST)
	@echo "🔍 בודק זליגת זיכרון..."
	valgrind --leak-check=full --track-origins=yes ./$(TARGET_TEST)

valgrind-game: $(TARGET_MAIN)
	@echo "🔍 בודק זליגת זיכרון במערכת החינוכית..."
	valgrind --leak-check=full ./$(TARGET_MAIN) --console

# =========================
# ניקוי
# =========================
clean:
	@echo "🧹 מנקה קבצים בינאריים..."
	rm -f $(TARGET_MAIN) $(TARGET_TEST) $(TARGET_ORIGINAL)
	rm -f demo_main.cpp

clean-all: clean
	@echo "🧹 ניקוי מלא..."
	rm -f *.o *.gch core

# =========================
# מידע ועזרה
# =========================
info:
	@echo "=================================================================="
	@echo "🎯 Graph Algorithms Educational Game System"
	@echo "   מערכת חינוכית לאלגוריתמי גרפים"
	@echo "=================================================================="
	@echo "📊 מידע על המערכת:"
	@echo "   SFML זמין: $(SFML_AVAILABLE)"
	@if [ "$(SFML_AVAILABLE)" = "yes" ]; then \
		echo "   גרסת SFML: $$(pkg-config --modversion sfml-graphics 2>/dev/null || echo 'לא ידועה')"; \
		echo "   מאפיינים: ויזואליזציה אינטראקטיבית, אנימציות, מצב צעד אחר צעד"; \
	else \
		echo "   מצב: קונסולה בלבד"; \
		echo "   מאפיינים: הדגמות טקסט, בדיקות, אלגוריתמים בסיסיים"; \
	fi
	@echo "   קומפיילר: $(CXX)"
	@echo "   דגלים: $(CXXFLAGS)"
	@echo ""
	@echo "🎮 יעדים זמינים:"
	@echo "   make              - בניית המערכת החינוכית (ברירת מחדל)"
	@echo "   make game         - הרצת המשחק החינוכי"
	@echo "   make test         - הרצת בדיקות"
	@echo "   make original     - הדגמה מקורית פשוטה"
	@echo ""
	@echo "🎯 מצבי הרצה מיוחדים:"
	@echo "   make step-mode    - מצב צעד אחר צעד (למידה איטית)"
	@echo "   make auto-mode    - מצב אוטומטי (הדגמה מהירה)"
	@echo "   make console-demo - הדגמה בקונסולה"
	@echo "   make random-graph - יצירת גרף אקראי"
	@echo ""
	@echo "🔧 כלי פיתוח:"
	@echo "   make valgrind     - בדיקת זליגת זיכרון (בדיקות)"
	@echo "   make valgrind-game- בדיקת זליגת זיכרון (משחק)"
	@echo "   make clean        - ניקוי קבצים בינאריים"
	@echo "   make info         - מידע זה"
	@echo "   make install-sfml - התקנת SFML"
	@echo ""
	@if [ "$(SFML_AVAILABLE)" = "yes" ]; then \
		echo "✅ המערכת מוכנה למשחק אינטראקטיבי!"; \
		echo "🎓 מושלם ללימוד אלגוריתמים בכיתה או בבית"; \
	else \
		echo "📝 מערכת קונסולית מוכנה"; \
		echo "💡 התקן SFML לחוויה אינטראקטיבית מלאה"; \
	fi
	@echo "=================================================================="

# התקנת SFML
install-sfml:
	@echo "📦 מתקין SFML..."
	@if command -v apt-get >/dev/null 2>&1; then \
		echo "🐧 Ubuntu/Debian מזוהה - מתקין עם apt..."; \
		sudo apt update && sudo apt install -y libsfml-dev pkg-config; \
		echo "✅ SFML הותקן! הרץ 'make info' לוודא"; \
	elif command -v brew >/dev/null 2>&1; then \
		echo "🍎 macOS מזוהה - מתקין עם brew..."; \
		brew install sfml pkg-config; \
		echo "✅ SFML הותקן! הרץ 'make info' לוודא"; \
	elif command -v pacman >/dev/null 2>&1; then \
		echo "🏹 Arch Linux מזוהה - מתקין עם pacman..."; \
		sudo pacman -S sfml; \
		echo "✅ SFML הותקן! הרץ 'make info' לוודא"; \
	elif command -v yum >/dev/null 2>&1; then \
		echo "🎩 Red Hat/CentOS מזוהה - מתקין עם yum..."; \
		sudo yum install sfml-devel; \
		echo "✅ SFML הותקן! הרץ 'make info' לוודא"; \
	else \
		echo "❌ מערכת הפעלה לא נתמכת אוטומטית"; \
		echo "💡 התקן SFML ידנית:"; \
		echo "   Windows: vcpkg install sfml"; \
		echo "   מקור: https://www.sfml-dev.org/download.php"; \
	fi

# עזרה מפורטת
help: info
	@echo ""
	@echo "🎓 מדריך שימוש למורים וסטודנטים:"
	@echo ""
	@echo "👨‍🏫 למורים:"
	@echo "   1. make install-sfml  # התקנה חד פעמית"
	@echo "   2. make              # בניית המערכת"
	@echo "   3. make game         # הרצה בכיתה"
	@echo "   4. השתמש במקשים 1-5 להרצת אלגוריתמים שונים"
	@echo "   5. לחץ על קודקודים לבחירת נקודת התחלה"
	@echo ""
	@echo "👩‍🎓 לסטודנטים:"
	@echo "   • make step-mode    - למידה איטית וקפדנית"
	@echo "   • השתמש ב-SPACE למעבר בין שלבים"
	@echo "   • לחץ 'S' להחלפה בין מצבים"
	@echo "   • לחץ 'R' לאיפוס"
	@echo ""
	@echo "🔬 למפתחים:"
	@echo "   • כל המחלקות המקוריות נשמרו ללא שינוי"
	@echo "   • רק נוספה שכבת ויזואליזציה"
	@echo "   • make test לוודא שהכל עובד"
	@echo "   • make valgrind לבדיקת זיכרון"

# יעד לבניה מהירה (ללא אופטימיזציות כבדות)
fast: CXXFLAGS += -O0
fast: $(TARGET_MAIN)
	@echo "⚡ בניה מהירה הושלמה (ללא אופטימיזציות)"

# יעד לבניה מאופטמת (לשחרור)
release: CXXFLAGS += -O3 -DNDEBUG
release: $(TARGET_MAIN)
	@echo "🚀 בניה מאופטמת הושלמה (למכירה/הפצה)"

# =========================
# הערות חשובות למפתח:
# =========================
# 1. כל המחלקות המקוריות שלך נשארו ללא שינוי
# 2. רק נוספו קבצי המערכת החינוכית החדשה
# 3. Button.h יכול להימחק - החלפנו בפתרון משולב
# 4. GraphVisualizer.cpp הישן יכול להימחק - בנינו מערכת חדשה
# 5. main.cpp הוחלף במערכת חדשה
# =========================