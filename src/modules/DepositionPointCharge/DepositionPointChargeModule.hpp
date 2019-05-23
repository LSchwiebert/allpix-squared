/**
 * @file
 * @brief Definition of a module to deposit charges at a specific point
 * @copyright Copyright (c) 2017 CERN and the Allpix Squared authors.
 * This software is distributed under the terms of the MIT License, copied verbatim in the file "LICENSE.md".
 * In applying this license, CERN does not waive the privileges and immunities granted to it by virtue of its status as an
 * Intergovernmental Organization or submit itself to any jurisdiction.
 */

#include <string>

#include "core/module/Module.hpp"

namespace allpix {
    /**
     * @ingroup Modules
     * @brief Module to deposit charges at predefined positions in the sensor volume
     *
     * This module can deposit charge carriers at defined positions inside the sensitive volume of the detector
     */
    class DepositionPointChargeModule : public Module {
        /**
         * @brief Types of deposition
         */
        enum class DepositionModel {
            NONE = 0, ///< No deposition
            POINT,    ///< Deposition at a specific point
            SCAN,     ///< Scan through the volume of a pixel
            MIP,      ///< MIP-like linear deposition of charge carriers
        };

    public:
        /**
         * @brief Constructor for a module to deposit charges at a specific point in the detector's active sensor volume
         * @param config Configuration object for this module as retrieved from the steering file
         * @param messenger Pointer to the messenger object to allow binding to messages on the bus
         * @param detector Pointer to the detector for this module instance
         */
        DepositionPointChargeModule(Configuration& config, Messenger* messenger, std::shared_ptr<Detector> detector);

        /**
         * @brief Initialize the histograms
         */
        void init(std::mt19937_64&) override;

        /**
         * @brief Deposit charge carriers for every simulated event
         */
        void run(Event*) override;

    private:
        /**
         * @brief Helper function to deposit charges at a single point
         * @param event Pointer to current event
         */
        void DepositPoint(Event* event) const;

        /**
         * @brief Helper function to deposit charges along a line
         * @param event Pointer to current event
         */
        void DepositLine(Event* event) const;

        std::shared_ptr<Detector> detector_;

        DepositionModel model_;
        ROOT::Math::XYZVector voxel_;
        unsigned int root_, carriers_;
    };
} // namespace allpix
