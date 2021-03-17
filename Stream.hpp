/**
 * Copyright ©2021. Brent Weichel. All Rights Reserved.
 * Permission to use, copy, modify, and/or distribute this software, in whole
 * or part by any means, without express prior written agreement is prohibited.
 */
#pragma once
 
template < typename Type >
class Stream
{
public:
	Stream()
	{
	}

	Stream( Stream&& other )
	{
	}

	Stream( const Stream& other )
	{
	}

	size_t count( std::function< bool ( const Type& ) > predicate )
	{
	}

	Stream& filter( std::function< bool ( const Type& ) > predicate )
	{
	}

	Stream& foreach( std::function< void ( const Type& ) > function )
	{
	}

	Stream& foreach( std::function<> function )
	{
	}

	template < typename MappedType >
	Stream< MappedType > map( std::function< bool ( MappedType&, const Type& ) > mapper )
	{
	}

	template < typename KeyType >
	std::map< KeyType, Stream< Type > > partition( std::function< void ( KeyType&, const Type& ) > partitioner )
	{
	}

	template < typename ReductionType >
	ReductionType reduce( std::function< void ( ReductionType&, const Type& ) > reducer, ReductionType initializer =  )
	{
	}
};
