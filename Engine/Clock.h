#ifndef QUANTVERSO_CLOCK_H
#define QUANTVERSO_CLOCK_H

//--------------------------------------------------------------------------------------------------

#include <chrono>

using namespace std::chrono;
using Time = time_point<high_resolution_clock>;
using Elapsed = duration<float>;

//--------------------------------------------------------------------------------------------------

class Clock
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Retorna o tempo decorrido desde a �ltima chamada deste m�todo.
    /// 
    /// Calcula e retorna o intervalo de tempo transcorrido entre a chamada atual
    /// e a chamada anterior de ElapsedTime(). Para a primeira chamada,
    /// o valor retornado ser� o tempo decorrido desde a cria��o da inst�ncia.
    /// 
    /// \return float Tempo decorrido em segundos.
    /// 
    ////////////////////////////////////////////////////////////
    float ElapsedTime();

    ////////////////////////////////////////////////////////////
    /// \brief Retorna o tempo decorrido desde a �ltima chamada de Reset().
    /// 
    /// Fornece o tempo acumulado desde a �ltima chamada do m�todo Reset() ou do
    /// momento em que o rel�gio foi instanciado.
    /// 
    /// \return float Tempo acumulado desde a �ltima chamada de Reset() em segundos.
    /// 
    ////////////////////////////////////////////////////////////
    float Count();

    ////////////////////////////////////////////////////////////
    /// \brief Reinicia o contador de tempo global da inst�ncia.
    /// 
    /// Este m�todo reinicializa o contador utilizado para as medi��es de tempo,
    /// de forma que o m�todo Count() inicie uma nova contagem a partir do momento da chamada.
    /// 
    ////////////////////////////////////////////////////////////
    void Reset();

private:
    Time    m_First{ high_resolution_clock::now() };
    Time    m_Last{ m_First };
    Time    m_Current{ m_First };
    Elapsed m_Elapsed{ Elapsed::zero() };
};

//--------------------------------------------------------------------------------------------------

inline float Clock::ElapsedTime()
{
    m_Elapsed = Elapsed((m_Current = high_resolution_clock::now()) - m_Last);
    m_Last = m_Current;
    return m_Elapsed.count();
}

//--------------------------------------------------------------------------------------------------

inline float Clock::Count()
{
    m_Elapsed = Elapsed(high_resolution_clock::now() - m_First);
    return m_Elapsed.count();
}

//--------------------------------------------------------------------------------------------------

inline void Clock::Reset()
{
    m_First = high_resolution_clock::now();
}

//--------------------------------------------------------------------------------------------------

#endif
