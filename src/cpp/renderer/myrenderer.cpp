#include "renderer/myrenderer.h"

namespace renderer {

    void MyRenderer::drawLine2(const glm::vec2& start, const glm::vec2& end, const glm::vec4& color) {
        Line2 lines[] = { {start, color}, {end, color} };
        uint32_t i;

        for (i = 0; i < 2; ++i) {
            Line2 line = lines[i];
            bool added = false;
            for (auto& batch : line2Batches) {
                if (batch.add(line)) {
                    added = true;
                    break;
                }
            }
            if (!added) {
                BatchRenderer<Line2> batch{};
                batch.init();
                batch.add(line);
                line2Batches.push_back(batch);
                batches.push_back(&batch);
            }
        }
    }
}
