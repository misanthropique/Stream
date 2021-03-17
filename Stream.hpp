/**
 * Copyright ©2021. Brent Weichel. All Rights Reserved.
 * Permission to use, copy, modify, and/or distribute this software, in whole
 * or part by any means, without express prior written agreement is prohibited.
 */
#pragma once

#include <vector>
#include <type_traits>

/*
 * There are a few branching points to consider.
 * Eager vs Lazy execution, Immutable vs Mutable,
 * Ordered vs Unordered, and number of threads.
 * By default the contents of stream shall be mutable and ordered.
 */
template < typename Type,
	bool _Mutable = true,
	bool _Ordered = true >
class Stream
{
	std::vector< Type > mDataSource;

public:
	
	using StreamReturnType = std::conditional< _Mutable, Stream&, Stream >::type;

	Stream()
	{
	}

	Stream( Stream&& other )
	{
	}

	Stream( const Stream& other )
	{
	}

	Stream( std::initializer_list< Type > initList )
	{
	}

	Stream( std::vector< Type >&& source )
	{
	}

	template < typename Collector >
	void collect( Collector< Type >& sink )
	{
	}

	size_t count( std::function< bool ( const Type& ) > predicate )
	{
		// Counting is unaffected by mutability or order
		// So this is trivially parallelizable.
		size_t counter( 0 );
		for ( auto& value : mDataSource )
		{
			if ( predicate( value ) )
			{
				++counter;
			}
		}

		return counter;
	}

	StreamReturnType filter( std::function< bool ( const Type& ) > predicate )
	{
		for ( auto iter = mDataSource.begin(); iter != mDataSource.end(); )
		{
			if ( predicate( *iter ) )
			{
				++iter;
			}
			else
			{
				iter = mDataSource.erase( iter );
			}
		}

		return *this;
	}

	void foreach( std::function< void ( Type& ) > function )
	{
		
	}

	void foreach( std::function< void ( const Type& ) > function )
	{
		for ( auto& value : mDataSource )
		{
			function( value );
		}

		return *this;
	}

	template < typename MappedType >
	Stream< MappedType > map( std::function< bool ( MappedType&, const Type& ) > mapper )
	{
		Stream< MappedType > mappedStream;
		MappedType mappedValue;

		for ( auto& value : mDataSource )
		{
			if ( mapper( mappedValue, value ) )
			{
				mappedStream.mDataSource.push_back( std::move( mappedValue ) );
			}
		}

		return std::move( mappedStream );
	}

	template < typename KeyType >
	std::map< KeyType, Stream< Type > > partition( std::function< void ( KeyType&, const Type& ) > partitioner )
	{
		std::map< KeyType, Stream< Type > > partitionedStreams;
		KeyType partitionKey;

		for ( auto& value : mDataSource )
		{
			partitioner( partitionKey, value );
			if ( partitionedStreams.end() == partitionedStreams.find( partitionKey ) )
			{
			}
			else
			{
				partitionedStreams[ partitionKey ].mDataSource.push_back( std::
			}
		}
	}

	template < typename ReductionType >
	ReductionType reduce( std::function< void ( ReductionType&, const Type& ) > reducer, ReductionType initializer = ReductionType() )
	{
		return std::move( initializer );
	}
};
