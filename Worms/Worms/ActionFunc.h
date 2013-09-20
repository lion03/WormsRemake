/**
\file	ActionFunc.h

\brief	Declares the action function class.
This Class is initial base for delegate pattern,
The main pattern that is used for implementation of GUI
in VC++ and C#,
In an abstract base is used to get the possibility of storing
functions with different signatures in single container and to trigger 
them from it.
*/

#pragma once
#include <SFML/Graphics.hpp>
#include<functional>

/**
\brief	class GuiObject;
*/

class ActionFunc
{
public:

	/**
	\brief	Initializes a new instance of the ActionFunc class.
	*/

	ActionFunc(void){};

	/**
	\brief	Actions this object.
	*/

	virtual void Action() = 0;

	/**
	\brief	Finalizes an instance of the ActionFunc class.
	*/

	virtual ~ActionFunc(){};

private:

	sf::Event::EventType m_ActivatingEventType; ///< Type of the activating event

};

/**
\brief	Action function 0 argument.

\tparam	Pmf	Type of the pmf.

\sa	ActionFunc
*/

template<class Pmf>
class ActionFunc0Arg : public ActionFunc
{
public:

	/**
	 \brief	Initializes a new instance of the ActionFunc0Arg class.
	
	 \param	func			  	The function.
	 \param [in,out]	target	If non-null, target for the.
	 */

	ActionFunc0Arg(const std::tr1::_Mem_fn1<void,void(Pmf::*)(),Pmf> & func,Pmf *target):m_Func(func),m_Target(target){};

	/**
	\brief	Actions this object.
	*/

	virtual void Action() {m_Func(m_Target);}

	/**
	\brief	Actions the given target.

	\param [in,out]	target	Target for the.
	*/

	virtual void Action(Pmf &target){m_Func(&target);}

	/**
	 \brief	Finalizes an instance of the ActionFunc0Arg class.
	 */

	virtual ~ActionFunc0Arg(void){};

private:

	std::tr1::_Mem_fn1<void,void(Pmf::*)(),Pmf> m_Func; ///< The function

	Pmf *m_Target;  ///< Target for the
};

/**
\brief	Action function 1 argument.

\tparam	P  	Type of the p.
\tparam	Arg	Type of the argument.

\sa	ActionFunc
*/

template<class P ,class Arg>
class ActionFunc1Arg : public ActionFunc

{
public:

	/**
	 \brief	Initializes a new instance of the ActionFunc1Arg class.
	
	 \param	func			  	The function.
	 \param [in,out]	target	If non-null, target for the.
	 \param	arg				  	The argument.
	 */

	ActionFunc1Arg(const std::tr1::_Mem_fn2<void,void (P::*)(Arg),P,Arg> &func,P* target,const Arg &arg):m_Func(func),m_Target(target), m_Arg(arg){};

	/**
	\brief	Finalizes an instance of the ActionFunc1Arg class.
	*/

	virtual ~ActionFunc1Arg(){};

	/**
	\brief	Actions this object.
	*/

	virtual void Action(void){m_Func(m_Target,m_Arg);}

	/**
	\brief	Actions.

	\tparam	DestObj	Type of the destination object.
	\param [in,out]	dest	Destination for the.
	\param	arg					The argument.
	*/

	template<class DestObj>

	/**
	 \brief	Actions.
	
	 \param [in,out]	dest	Destination for the.
	 \param	arg					The argument.
	 */

	void Action(DestObj &dest ,const Arg & arg){m_Func(dest, arg);}

private:

	std::tr1::_Mem_fn2<void,void(P::*)(Arg),P,Arg> m_Func;  ///< The function

	P* m_Target;	///< Target for the

	Arg m_Arg;  ///< The argument

};

/**
 \brief	Action function 2 argument.

 \tparam	P   	Type of the p.
 \tparam	Arg1	Type of the argument 1.
 \tparam	Arg2	Type of the argument 2.

 \sa	ActionFunc
 */

template<class P ,class Arg1, class Arg2>
class ActionFunc2Arg : public ActionFunc

{
public:

	/**
	 \brief	Initializes a new instance of the ActionFunc2Arg class.
	
	 \param	func			  	The function.
	 \param [in,out]	target	If non-null, target for the.
	 \param	arg1			  	The first argument.
	 \param	arg2			  	The second argument.
	 */

	ActionFunc2Arg(const std::tr1::_Mem_fn3<void,void (P::*)(Arg1,Arg2),P,Arg1,Arg2> &func,P* target,const Arg1& arg1,const Arg2 &arg2):m_Func(func),m_Target(target), m_Arg1(arg1),m_Arg2(arg2){};

	/**
	\brief	Finalizes an instance of the ActionFunc1Arg class.
	*/

	virtual ~ActionFunc2Arg(){};

	/**
	\brief	Actions this object.
	*/

	virtual void Action(void){m_Func(m_Target,m_Arg1,m_Arg2);}

	/**
	 \brief	Actions.
	
	 \tparam	DestObj	Type of the destination object.
	 \param [in,out]	dest	Destination for the.
	 \param	arg					The argument.
	 \param	arg2				The second argument.
	 */

	template<class DestObj>
	void Action(DestObj &dest ,const Arg1 & arg, const Arg2 &arg2){m_Func(dest, arg,arg2);}

private:

	std::tr1::_Mem_fn3<void,void(P::*)(Arg1,Arg2),P,Arg1,Arg2> m_Func;  ///< The function

	P* m_Target;	///< Target for the

	Arg1 m_Arg1;  ///< The argument

	Arg2 m_Arg2;	///< The second m argument

};