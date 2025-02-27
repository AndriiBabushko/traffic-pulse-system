//
// Created by andrii on 2/11/25.
//

#ifndef PULSE_PEDESTRIAN_H
#define PULSE_PEDESTRIAN_H

#include <string>

#include <types/PulsePosition.h>
#include <libsumo/Person.h>

namespace Pulse {
    /**
     * @brief Клас PulsePedestrian репрезентує пішохода.
     */
    class PulsePedestrian
    {
    private:
        std::string pedestrian_id; ///< Ідентифікатор пішохода в SUMO.
        PulsePosition position;   ///< Поточна позиція пішохода.
        double speed;

    public:
        /**
         * @brief Створює об'єкт пішохода за його ідентифікатором у SUMO.
         * @param pedestrian_id Ідентифікатор (ID) пішохода в SUMO.
         */
        explicit PulsePedestrian(const std::string& pedestrian_id, const PulsePosition& position = {0.0, 0.0}, const double& speed = 0.0);

        /**
         * @brief Повертає ідентифікатор цього пішохода.
         * @return Строковий ID, яким користується SUMO.
         */
        [[nodiscard]] std::string getId() const;

        /**
         * @brief Отримати поточну швидкість пішохода в м/с.
         * @return Поточна швидкість у метрах за секунду.
         */
        [[nodiscard]] double getSpeed() const;

        /**
         * @brief Отримати поточну позицію (x,y) пішохода.
         * @return Пара (x, y) як `std::pair<double, double>`.
         */
        [[nodiscard]] std::pair<double, double> getPosition() const;

        /**
         * @brief Оновити дані про пішохода із SUMO (позиція, швидкість тощо).
         */
        void update();
    };
}

#endif // PULSE_PEDESTRIAN_H

