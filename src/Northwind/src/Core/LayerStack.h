#pragma once

#include "nwpch.h"

#include "Core/Core.h"
#include "Layer.h"

namespace Northwind {

	class LayerStack {
	public:
		explicit LayerStack ();
		~LayerStack ();

		void pushLayer (const Ref<Layer>& layer);
		void popLayer (Layer* layer);
		void pushOverlay (const Ref<Layer>& overlay);
		void popOverlay (Layer* overlay);


		std::vector<Layer*>::iterator begin () { return m_layers.begin (); }
		std::vector<Layer*>::iterator end () { return m_layers.end (); }
		std::vector<Layer*>::const_iterator cbegin () const { return m_layers.cbegin (); }
		std::vector<Layer*>::const_iterator cend () const { return m_layers.cend (); }

		std::vector<Layer*>::reverse_iterator rbegin () { return m_layers.rbegin (); }
		std::vector<Layer*>::reverse_iterator rend () { return m_layers.rend (); }
		std::vector<Layer*>::const_reverse_iterator crbegin () const { return m_layers.crbegin (); }
		std::vector<Layer*>::const_reverse_iterator crend () const { return m_layers.crend (); }



	private:
		std::vector<Layer*> m_layers;
		std::vector<Ref<Layer>> m_layersStorage;
		ptrdiff_t m_layerInsertIndex = 0;
	};

}