cmake_minimum_required(VERSION 3.16)
project(GraphVisualizerSystem LANGUAGES CXX)

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
find_package(sfml-graphics QUIET)
find_package(sfml-window QUIET)
find_package(sfml-system QUIET)

# בדיקה אם SFML נמצא
set(SFML_FOUND FALSE)
if(sfml-graphics_FOUND AND sfml-window_FOUND AND sfml-system_FOUND)
    set(SFML_FOUND TRUE)
    message(STATUS "✅ SFML נמצא - מערכת גרפית תיבנה")
else()
    message(WARNING "⚠️  SFML לא נמצא - רק מערכת קונסולית תיבנה")
    message(STATUS "התקן SFML עם: sudo apt-get install libsfml-dev (Ubuntu/Debian)")
    message(STATUS "או עם: brew install sfml (macOS)")
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
)

# ===== יעד 1: המטלה המקורית (קונסולה) =====
add_executable(OriginalGraphSystem
        main_original.cpp  # גיבוי של ה-main המקורי
        ${CORE_SOURCES}
)

# ===== יעד 2: מערכת הבדיקות =====
add_executable(GraphTests
        ${CORE_SOURCES}
        ${TEST_SOURCES}
)

# ===== יעד 3: מערכת ויזואליזציה (אם SFML קיים) =====
if(SFML_FOUND)
    # קבצי GUI
    set(GUI_SOURCES
            GraphVisualizer.cpp
            GraphVisualizer.h
    )

    add_executable(GraphVisualizerSystem
            main.cpp  # ה-main החדש עם GUI
            ${CORE_SOURCES}
            ${GUI_SOURCES}
    )

    # קישור SFML
    target_link_libraries(GraphVisualizerSystem
            sfml-graphics
            sfml-window
            sfml-system
    )

    # הגדרות נוספות ל-SFML
    target_compile_definitions(GraphVisualizerSystem PRIVATE
            SFML_AVAILABLE=1
    )

    # העתקת פונטים אם יש
    if(EXISTS "${CMAKE_SOURCE_DIR}/fonts/arial.ttf")
        configure_file("${CMAKE_SOURCE_DIR}/fonts/arial.ttf"
                "${CMAKE_BINARY_DIR}/arial.ttf" COPYONLY)
    endif()

    message(STATUS "✅ GraphVisualizerSystem נוצר עם תמיכה ב-SFML")
endif()

# ===== יעד 4: main היברידי (פועל תמיד) =====
add_executable(GraphSystemHybrid
        main.cpp
        ${CORE_SOURCES}
)

# אם SFML קיים, הוסף תמיכה גרפית
if(SFML_FOUND)
    target_sources(GraphSystemHybrid PRIVATE
            GraphVisualizer.cpp
            GraphVisualizer.h
    )
    target_link_libraries(GraphSystemHybrid
            sfml-graphics
            sfml-window
            sfml-system
    )
    target_compile_definitions(GraphSystemHybrid PRIVATE
            SFML_AVAILABLE=1
    )
else()
    # אם אין SFML, הוסף דגל שיגיד למערכת לעבוד רק בקונסולה
    target_compile_definitions(GraphSystemHybrid PRIVATE
            CONSOLE_ONLY=1
    )
endif()

# ===== יעדי BUILD נוחים =====
add_custom_target(run-original
        COMMAND OriginalGraphSystem
        DEPENDS OriginalGraphSystem
        COMMENT "מריץ את המטלה המקורית"
)

add_custom_target(run-tests
        COMMAND GraphTests
        DEPENDS GraphTests
        COMMENT "מריץ את כל הבדיקות"
)

if(SFML_FOUND)
    add_custom_target(run-gui
            COMMAND GraphVisualizerSystem
            DEPENDS GraphVisualizerSystem
            COMMENT "מריץ את המערכת הגרפית"
    )
endif()

add_custom_target(run-hybrid
        COMMAND GraphSystemHybrid
        DEPENDS GraphSystemHybrid
        COMMENT "מריץ את המערכת ההיברידית"
)

# ===== יעדי ניקוי =====
add_custom_target(clean-all
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}
        COMMENT "מנקה את כל קבצי ה-build"
)

# ===== הדפסת מידע =====
message(STATUS "==========================================")
message(STATUS "📊 סיכום מערכת הויזואליזציה לגרפים")
message(STATUS "==========================================")
message(STATUS "יעדים זמינים:")
message(STATUS "  • OriginalGraphSystem    - המטלה המקורית")
message(STATUS "  • GraphTests            - מערכת בדיקות")
message(STATUS "  • GraphSystemHybrid     - מערכת היברידית")

if(SFML_FOUND)
    message(STATUS "  • GraphVisualizerSystem - מערכת גרפית מלאה ✅")
    message(STATUS "")
    message(STATUS "📝 הרצה:")
    message(STATUS "  make run-gui       # מערכת גרפית")
    message(STATUS "  make run-tests     # בדיקות")
    message(STATUS "  make run-original  # מטלה מקורית")
else()
    message(STATUS "  • GraphVisualizerSystem - לא זמין (חסר SFML) ❌")
    message(STATUS "")
    message(STATUS "📝 הרצה:")
    message(STATUS "  make run-hybrid    # מערכת קונסולית")
    message(STATUS "  make run-tests     # בדיקות")
    message(STATUS "  make run-original  # מטלה מקורית")
endif()

message(STATUS "==========================================")

# הגדרות נוספות לדיבוג
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "🔧 מצב Debug מופעל")
    add_compile_definitions(DEBUG_MODE=1)
endif()