// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#include "mx/core/elements/Dashes.h"
#include "mx/core/FromXElement.h"
#include <iostream>

namespace mx
{
    namespace core
    {
        Dashes::Dashes()
        :ElementInterface()
        ,myAttributes( std::make_shared<DashesAttributes>() )
        {}


        bool Dashes::hasAttributes() const
        {
            return myAttributes->hasValues();
        }


        bool Dashes::hasContents() const  { return false; }
        std::ostream& Dashes::streamAttributes( std::ostream& os ) const
        {
            if ( myAttributes )
            {
                myAttributes->toStream( os );
            }
            return os;
        }


        std::ostream& Dashes::streamName( std::ostream& os ) const  { os << "dashes"; return os; }
        std::ostream& Dashes::streamContents( std::ostream& os, const int indentLevel, bool& isOneLineOnly ) const
        {
            MX_UNUSED( indentLevel );
            isOneLineOnly = true;
            return os;
        }


        DashesAttributesPtr Dashes::getAttributes() const
        {
            return myAttributes;
        }


        void Dashes::setAttributes( const DashesAttributesPtr& value )
        {
            if ( value )
            {
                myAttributes = value;
            }
        }


        bool Dashes::fromXElementImpl( std::ostream& message, ::ezxml::XElement& xelement )
        {
            return myAttributes->fromXElement( message, xelement );
        }

    }
}
