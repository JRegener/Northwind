#include "LayerStack.h"


namespace Northwind {



	LayerStack::LayerStack()
	{
	}

	LayerStack::~LayerStack()
	{
		NW_PROFILE_FUNC();

		for (auto layer : m_layers)
		{
			layer->OnDetach();
		}
	}

	void LayerStack::pushLayer(const Ref<Layer>& layer)
	{
		NW_PROFILE_FUNC();

		m_layersStorage.push_back(layer);
		m_layers.emplace(m_layers.begin() + m_layerInsertIndex, layer.get());
		m_layerInsertIndex++;
	}

	void LayerStack::popLayer(Layer* layer)
	{
		NW_PROFILE_FUNC();

		auto it = std::find(m_layers.begin(), m_layers.begin() + m_layerInsertIndex, layer);
		if (it != m_layers.begin() + m_layerInsertIndex) {
			layer->OnDetach();
			m_layers.erase(it);
			m_layerInsertIndex--;
		}
	}

	void LayerStack::pushOverlay(const Ref<Layer>& overlay)
	{
		NW_PROFILE_FUNC();

		m_layersStorage.push_back(overlay);
		m_layers.emplace_back(overlay.get());
	}

	void LayerStack::popOverlay(Layer* overlay)
	{
		NW_PROFILE_FUNC();

		auto it = std::find(m_layers.begin() + m_layerInsertIndex, m_layers.end(), overlay);
		if (it != m_layers.end()) {
			overlay->OnDetach();
			m_layers.erase(it);
		}
	}

}