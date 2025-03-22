//
// Created by andrii on 2/22/25.
//

#pragma once

#ifndef TRAFFICSYSTEM_H
#define TRAFFICSYSTEM_H

#include <memory>
#include <vector>
#include <string>
#include <atomic>
#include "interfaces/ISubject.h"

/**
 * @brief Main system class for traffic pulse.
 *
 * This class creates and manages its own modules (SumoIntegration, PulseDataManager, PulseTrafficAlgo)
 * and runs the simulation loop. It acts as a Subject so that observers (like a UI or Logger) can be notified
 * about system events (using, for example, the PulseEvents enum).
 *
 * The simulation runs continuously until the user requests a stop.
 */
class TrafficSystem : public ISubject {
public:
    /**
     * @brief Constructs a TrafficSystem.
     * @param updateFrequency The frequency (in seconds) at which the system updates and notifies observers.
     */
    explicit TrafficSystem(double updateFrequency = 5.0);

    ~TrafficSystem() override;

    /**
     * @brief Runs the simulation loop continuously until a stop is requested.
     */
    void run();

    /**
     * @brief Requests the simulation to stop.
     *
     * This method can be called from another thread or context to signal the simulation loop to exit.
     */
    void requestStop();

    /**
     * @brief Attach an observer to receive events.
     * @param observer Shared pointer to the observer.
     */
    void attach(std::shared_ptr<class IObserver> observer) override;

    /**
     * @brief Detach an observer.
     * @param observer Shared pointer to the observer.
     */
    void detach(std::shared_ptr<class IObserver> observer) override;

    /**
     * @brief Notifies all attached observers with an event description.
     * @param eventDescription The description of the event.
     */
    void notify(const std::string& eventDescription) override;

    /**
     * @brief Provides access to the data manager.
     */
    [[nodiscard]] class PulseDataManager& getDataManager() const;

private:
    // Internal modules; created internally.
    std::unique_ptr<class SumoIntegration> m_sumo;
    // PulseDataManager is a singleton.
    class PulseDataManager& m_dataManager;
    std::unique_ptr<class PulseTrafficAlgo> m_algo;

    // Observer list
    std::vector<std::shared_ptr<class IObserver>> m_observers;

    // Simulation update frequency (in seconds)
    double m_updateFrequency;

    // Flag to signal simulation stop.
    std::atomic<bool> m_stopRequested{false};
};

#endif //TRAFFICSYSTEM_H
