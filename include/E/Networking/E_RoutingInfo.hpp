/**
 * @file   E_RoutingInfo.hpp
 * @Author leeopop (dlrmsghd@gmail.com)
 * @date   November, 2014
 * @brief  Header for E::RoutingInfo
 */

#ifndef E_ROUTINGINFO_HPP_
#define E_ROUTINGINFO_HPP_

#include <E/E_Common.hpp>

namespace E {

/**
 * @brief This class provides routing information
 * to its child class.
 */
class RoutingInfo {
private:
  struct mac_entry {
    mac_t mac;
    int port;
  };

  struct ip_entry {
    ipv4_t ip;
    int port;
  };

  struct arp_entry {
    ipv4_t ip;
    mac_t mac;
  };

  struct route_entry {
    ipv4_t ip_mask;
    int prefix;
    int port;
  };

  std::vector<struct mac_entry> mac_vector;
  std::vector<struct ip_entry> ip_vector;
  std::vector<struct arp_entry> arp_vector;
  std::vector<struct route_entry> route_vector;

public:
  RoutingInfo();
  virtual ~RoutingInfo();

public:
  /**
   * @param ip IP address.
   * @param port Interface index to bind the given IP address.
   * @note You cannot override this function.
   */
  virtual void setIPAddr(const ipv4_t &ip, int port) final;

  /**
   * @param mac MAC address.
   * @param port Interface index to bind the given MAC address.
   * @note You cannot override this function.
   */
  virtual void setMACAddr(const mac_t &mac, int port) final;

  /**
   * @brief Add (MAC,IP) entry to its ARP table.
   * @param mac MAC address.
   * @param ip IP address.
   * @note You cannot override this function.
   */
  virtual void setARPTable(const mac_t &mac, const ipv4_t &ipv4) final;

  /**
   * @param mask IP address mask.
   * @param prefix Prefix length for routing.
   * @param port Interface index to bind the given routing entry.
   * @note You cannot override this function.
   */
  virtual void setRoutingTable(const ipv4_t &mask, int prefix, int port) final;

  /**
   * @param ip_buffer Address of the buffer to save the IP address.
   * @param port Interface index to retrieve its IP address.
   * @return Whether this request is successful or not.
   * @note You cannot override this function.
   */
  virtual std::optional<ipv4_t> getIPAddr(int port) final;

  /**
   * @param mac_buffer Address of the buffer to save the MAC address.
   * @param port Interface index to retrieve its MAC address.
   * @return Whether this request is successful or not.
   * @note You cannot override this function.
   */
  virtual std::optional<mac_t> getMACAddr(int port) final;

  /**
   * @param mac_buffer Address of the buffer to save the MAC address.
   * @param ip_buffer IP address to find its corresponding MAC address.
   * @return Whether this request is successful or not.
   * @note You cannot override this function.
   */
  virtual std::optional<mac_t> getARPTable(const ipv4_t &ipv4) final;

  /**
   * @param ip_buffer IP address to find its destination.
   * @return Interface index to this packet should go to.
   * @note You cannot override this function.
   */
  virtual int getRoutingTable(const ipv4_t &ip_addr) final;
};

} // namespace E

#endif /* E_ROUTINGINFO_HPP_ */
