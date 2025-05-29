cmake_minimum_required(VERSION 3.16)
project(GraphVisualizerGameSystem LANGUAGES CXX)

# הגדרות C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# אפשרויות קומפילציה מתקדמות
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
endif()

# חיפוש SFML
find_package(PkgConfig)
pkg_check_modules(SFML QUIET sfml-all>=2.5)

if(NOT SFML_FOUND)
    find_package(sfml-graphics QUIET)
    find_package(sfml-window QUIET)
    find_package(sfml-system QUIET)

    if(sfml-graphics_FOUND AND sfml-window_FOUND AND sfml-system_FOUND)
        set(SFML_FOUND TRUE)
    endif()
endif()

# בדיקה אם SFML נמצא
if(SFML_FOUND)
    set(SFML_AVAILABLE TRUE)
    message(STATUS "✅ SFML נמצא - מערכת המשחק התחולית תיבנה")
else()
    set(SFML_AVAILABLE FALSE)
    message(WARNING "⚠️  SFML לא נמצא - רק מערכת קונסולית תיבנה")
    message(STATUS "התקן SFML עם: sudo apt-get install libsfml-dev (Ubuntu/Debian)")
    message(STATUS "או עם: brew install sfml (macOS)")
    message(STATUS "או עם: vcpkg install sfml (Windows)")
endif()

# קבצי מקור בסיסיים (המטלה המקורית)
set(CORE_SOURCES
        Graph.cpp
        Graph.h
        Node_V.cpp
        Node_V.h
        Algorithms.cpp
        Algorithms.h
        Queue.cpp
        Queue.h
        PropertyQueue.cpp
        PropertyQueue.h
        Helpers.h
        UnionFind.cpp
        UnionFind.h
        EdgeList.cpp
        EdgeList.h
)

# קבצי המערכת החדשה (המשחק החינוכי)
set(GAME_SOURCES
        GraphGameVisualizer.h
        GraphGameVisualizer.cpp
)

# קבצי בדיקות
set(TEST_SOURCES
        tests/algorithms_test.cpp
        tests/node_v_test.cpp
        tests/unionFind_test.cpp
        tests/queue_test.cpp
        tests/propertyQueue_test.cpp
        tests/helpers_test.cpp
        tests/edgeList_test.cpp
        tests/memory_test.cpp
        tests/graph_test.cpp
        FontManager.h
)

# ===== יעד 1: מערכת הבדיקות =====
add_executable(GraphTests
        ${CORE_SOURCES}
        ${TEST_SOURCES}
)

# ===== יעד 2: מערכת המשחק החינוכי =====
add_executable(GraphAlgorithmsGame
        main.cpp
        ${CORE_SOURCES}
)

# הוספת קבצי המשחק אם SFML זמין
if(SFML_AVAILABLE)
    target_sources(GraphAlgorithmsGame PRIVATE
            ${GAME_SOURCES}
    )

    if(SFML_LIBRARIES)
        # אם נמצא עם pkg-config
        target_link_libraries(GraphAlgorithmsGame ${SFML_LIBRARIES})
        target_include_directories(GraphAlgorithmsGame PRIVATE ${SFML_INCLUDE_DIRS})
        target_compile_options(GraphAlgorithmsGame PRIVATE ${SFML_CFLAGS_OTHER})
    else()
        # אם נמצא עם find_package
        target_link_libraries(GraphAlgorithmsGame
                sfml-graphics
                sfml-window
                sfml-system
        )
    endif()

    target_compile_definitions(GraphAlgorithmsGame PRIVATE
            SFML_AVAILABLE=1
    )

    message(STATUS "✅ GraphAlgorithmsGame נוצר עם תמיכה במשחק אינטראקטיבי")
else()
    # אם אין SFML, הוסף דגל שיגיד למערכת לעבוד רק בקונסולה
    target_compile_definitions(GraphAlgorithmsGame PRIVATE
            CONSOLE_ONLY=1
    )
    message(STATUS "📝 GraphAlgorithmsGame נוצר במצב קונסולה בלבד")
endif()

# ===== יעדי BUILD נוחים =====
add_custom_target(run-tests
        COMMAND GraphTests
        DEPENDS GraphTests
        COMMENT "מריץ את כל הבדיקות"
)

add_custom_target(run-game
        COMMAND GraphAlgorithmsGame
        DEPENDS GraphAlgorithmsGame
        COMMENT "מריץ את מערכת המשחק החינוכי"
)

add_custom_target(run-console-demo
        COMMAND GraphAlgorithmsGame --console
        DEPENDS GraphAlgorithmsGame
        COMMENT "מריץ הדגמה בקונסולה"
)

# ===== יעדי התקנה =====
if(SFML_AVAILABLE)
    # העתקת קבצי פונט נדרשים
    add_custom_command(TARGET GraphAlgorithmsGame POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E echo "Looking for font files..."
            COMMENT "בדיקת זמינות קבצי פונט"
    )
endif()

# ===== יעדי ניקוי =====
add_custom_target(clean-all
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}
        COMMENT "מנקה את כל קבצי ה-build"
)

# ===== הגדרות מיוחדות לפלטפורמות שונות =====
if(WIN32)
    # Windows specific settings
    if(SFML_AVAILABLE)
        # העתקת DLL files אם נדרש
        add_custom_command(TARGET GraphAlgorithmsGame POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E echo "Windows build with SFML support"
        )
    endif()
elseif(APPLE)
    # macOS specific settings
    if(SFML_AVAILABLE)
        set_target_properties(GraphAlgorithmsGame PROPERTIES
                MACOSX_BUNDLE TRUE
                MACOSX_BUNDLE_INFO_STRING "Graph Algorithms Educational Game"
                MACOSX_BUNDLE_BUNDLE_NAME "GraphAlgorithmsGame"
                MACOSX_BUNDLE_BUNDLE_VERSION "1.0"
                MACOSX_BUNDLE_SHORT_VERSION_STRING "1.0"
        )
    endif()
endif()

# ===== הדפסת מידע =====
message(STATUS "==========================================")
message(STATUS "🎯 Graph Algorithms Educational Game System")
message(STATUS "==========================================")
message(STATUS "יעדים זמינים:")
message(STATUS "  • GraphAlgorithmsGame    - המערכת החינוכי")
message(STATUS "  • GraphTests             - מערכת בדיקות")

if(SFML_AVAILABLE)
    message(STATUS "  ✅ תמיכה במשחק אינטראקטיבי מופעלת")
    message(STATUS "")
    message(STATUS "🎮 מאפיינים חינוכיים:")
    message(STATUS "  • ויזואליזציה אינטראקטיבית של אלגוריתמים")
    message(STATUS "  • ביצוע צעד אחר צעד עם הסברים")
    message(STATUS "  • הצגת מבני נתונים (תורים, מחסניות)")
    message(STATUS "  • אנימציות צבעוניות ומושכות")
    message(STATUS "  • מותאם לילדים ולסטודנטים")
    message(STATUS "")
    message(STATUS "📝 הרצה:")
    message(STATUS "  make run-game           # מערכת המשחק המלאה")
    message(STATUS "  make run-console-demo   # הדגמה בקונסולה")
    message(STATUS "  make run-tests          # בדיקות")
else()
    message(STATUS "  ❌ GUI לא זמין (חסר SFML)")
    message(STATUS "")
    message(STATUS "📝 הרצה:")
    message(STATUS "  make run-game           # מערכת קונסולית")
    message(STATUS "  make run-console-demo   # הדגמה בקונסולה")
    message(STATUS "  make run-tests          # בדיקות")
    message(STATUS "")
    message(STATUS "💡 להתקנת SFML:")
    message(STATUS "  Ubuntu/Debian: sudo apt-get install libsfml-dev")
    message(STATUS "  macOS: brew install sfml")
    message(STATUS "  Windows: vcpkg install sfml")
endif()

message(STATUS "")
message(STATUS "🎓 מערכת חינוכית לאלגוריתמי גרפים")
message(STATUS "   מושלמת לילדים, סטודנטים ומורים!")
message(STATUS "==========================================")