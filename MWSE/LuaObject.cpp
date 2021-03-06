#include "LuaObject.h"

namespace mwse::lua
{

std::unique_ptr< ObjectCreatorBase > makeObjectCreator( TES3::ObjectType::ObjectType objectType )
{
	switch( objectType )
	{
	case TES3::ObjectType::Activator:
		return std::make_unique< ObjectCreator< TES3::Activator > >();
	case TES3::ObjectType::Misc:
		return std::make_unique< ObjectCreator< TES3::Misc > >();
	case TES3::ObjectType::Static:
		return std::make_unique< ObjectCreator< TES3::Static > >();
	default:
		return std::make_unique< InvalidObjectCreator >();
	}
}

}