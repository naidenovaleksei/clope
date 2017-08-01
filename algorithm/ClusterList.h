#pragma once
#include "stdafx.h"
#include "Cluster.h"

static double R;

/**
*	ClusterList - класс для хранения и работы с кластерами
*	в процессе работы алгоритма CLOPE.
*	Абстрагирован от конкретной реализации хранения транзакции в памяти.
*	Использует интерфейс предоставляемый классом Transaction).
*
*/
template <typename Transaction>
class ClusterList
{
public:
	const int findProfitCluster( const Transaction &transaction );
	const int addTransaction( const Transaction &transaction );
	const int replaceTransaction( const Transaction &transaction );
	void deleteEmpty();

private:
	std::vector< Cluster<Transaction> > m_clusters;

};


template <typename Transaction>
const int ClusterList< Transaction >::findProfitCluster( const Transaction &transaction )
{
	Cluster< Transaction > newCluster;
	int index = 0;
	double delta;
	int maxClusterIndex;
	double maxDelta;


	maxClusterIndex = m_clusters.size();
	maxDelta = newCluster.deltaAdd( transaction );

	for ( auto p_cluster = m_clusters.begin(); p_cluster != m_clusters.end(); ++p_cluster )
	{
		if ( (delta = p_cluster->deltaAdd(transaction)) >= maxDelta ) {
			maxDelta = delta;
			maxClusterIndex = index;
		}
		++index;
	}
	return maxClusterIndex;
}


template <typename Transaction>
const int ClusterList< Transaction >::addTransaction( const Transaction &transaction )
{
	const int maxClusterIndex = findProfitCluster( transaction );

	if ( maxClusterIndex == m_clusters.size() ) 
		m_clusters.emplace_back( transaction );
	else 
		m_clusters[ maxClusterIndex ].add( transaction );

	return maxClusterIndex;
}


template <typename Transaction>
const int ClusterList< Transaction >::replaceTransaction( const Transaction &transaction )
{
	const int clusterIndex_old = transaction.clusterIndex();
	m_clusters[clusterIndex_old].remove( transaction );

	return addTransaction( transaction );
}


template <typename Transaction>
void ClusterList< Transaction >::deleteEmpty()
{
	for ( auto p_cluster = m_clusters.begin(); p_cluster != m_clusters.end(); ++p_cluster )
	{
		if ( p_cluster->empty() ) {
			m_clusters.erase( p_cluster );
			--p_cluster;
		}
	}
}
