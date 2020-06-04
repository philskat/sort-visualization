#include "sortengine.hpp"
#include "window.hpp"

SortEngine::SortEngine(const char* scriptPath)
{
    try
    {
        sol::usertype<List> list_type = m_State.new_usertype<List>("List", sol::constructors<List(unsigned int)>());
        sol::usertype<Rect> rect_type = m_State.new_usertype<Rect>("Rect", sol::constructors<Rect(int, int)>());

        list_type["getRectCount"] = &List::getRectCount;
        list_type["getRect"] = &List::getRect;
        list_type["swap"] = &List::swap;

        rect_type["getValue"] = &Rect::getValue;

        m_State.safe_script_file(scriptPath);

        m_State.set_function("getRunning", &SortEngine::getRunning, this);

        sol::function sort = m_State["sort"];

        m_Sort = sort;
    }
    catch (sol::error &e)
    {
        throw e;
    }
}

void SortEngine::sort(List* list)
{
    m_SortThread = std::thread(&SortEngine::sortMain, this, list);
}

void SortEngine::join()
{
    m_SortThread.join();
}

bool SortEngine::getRunning()
{
    return Window::running;
}

void SortEngine::sortMain(List* list)
{
    m_Sort(*list);
}