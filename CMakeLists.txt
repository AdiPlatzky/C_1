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
    message(STATUS "✅ SFML נמצא - מערכת גרפית תיבנה")
else()
    set(SFML_AVAILABLE FALSE)
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
        main_original.cpp  # גיבוי של ה-main המקורי אם יש
        ${CORE_SOURCES}
)

# ===== יעד 2: מערכת הבדיקות =====
add_executable(GraphTests
        ${CORE_SOURCES}
        ${TEST_SOURCES}
)

# ===== יעד 3: מערכת ויזואליזציה (היברידית) =====
add_executable(GraphVisualizerSystem
        main.cpp
        ${CORE_SOURCES}
)

# אם SFML זמין, הוסף תמיכה גרפית
if(SFML_AVAILABLE)
    target_sources(GraphVisualizerSystem PRIVATE
            GraphVisualizer.cpp
            GraphVisualizer.h
    )

    if(SFML_LIBRARIES)
        # אם נמצא עם pkg-config
        target_link_libraries(GraphVisualizerSystem ${SFML_LIBRARIES})
        target_include_directories(GraphVisualizerSystem PRIVATE ${SFML_INCLUDE_DIRS})
        target_compile_options(GraphVisualizerSystem PRIVATE ${SFML_CFLAGS_OTHER})
    else()
        # אם נמצא עם find_package
        target_link_libraries(GraphVisualizerSystem
                sfml-graphics
                sfml-window
                sfml-system
        )
    endif()

    target_compile_definitions(GraphVisualizerSystem PRIVATE
            SFML_AVAILABLE=1
    )

    message(STATUS "✅ GraphVisualizerSystem נוצר עם תמיכה ב-SFML")
else()
    # אם אין SFML, הוסף דגל שיגיד למערכת לעבוד רק בקונסולה
    target_compile_definitions(GraphVisualizerSystem PRIVATE
            CONSOLE_ONLY=1
    )
    message(STATUS "📝 GraphVisualizerSystem נוצר במצב קונסולה בלבד")
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

add_custom_target(run-visualizer
        COMMAND GraphVisualizerSystem
        DEPENDS GraphVisualizerSystem
        COMMENT "מריץ את מערכת הויזואליזציה"
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
message(STATUS "  • GraphVisualizerSystem - מערכת ויזואליזציה")
message(STATUS "  • GraphTests           - מערכת בדיקות")
message(STATUS "  • OriginalGraphSystem  - המטלה המקורית")

if(SFML_AVAILABLE)
    message(STATUS "  ✅ תמיכה ב-GUI מופעלת")
    message(STATUS "")
    message(STATUS "📝 הרצה:")
    message(STATUS "  make run-visualizer  # מערכת ויזואליזציה")
    message(STATUS "  make run-tests       # בדיקות")
    message(STATUS "  make run-original    # מטלה מקורית")
else()
    message(STATUS "  ❌ GUI לא זמין (חסר SFML)")
    message(STATUS "")
    message(STATUS "📝 הרצה:")
    message(STATUS "  make run-visualizer  # מערכת קונסולית")
    message(STATUS "  make run-tests       # בדיקות")
    message(STATUS "  make run-original    # מטלה מקורית")
endif()

message(STATUS "==========================================")